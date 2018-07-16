/*
 * =====================================================================================
 *
 *       Filename:  threadsafe_lookup_table.cpp
 *
 *    Description:  A thread-safe lookup table
 *
 *        Version:  1.0
 *        Created:  2018年07月16日 10时33分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <utility>
#include <mutex>
#include <shared_mutex>
#include <list>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>


template <typename Key, typename Value, typename Hash = std::hash<Key> >
class threadsafe_lookup_table {
private:
    class bucket_type {
    public:
        using bucket_value = std::pair<Key, Value>;
        using bucket_data = std::list<bucket_value>;
        using bucket_iterator = typename bucket_data::iterator;
        using bucket_const_iterator = typename bucket_data::const_iterator;

        bucket_data data;
        mutable std::shared_mutex mut;

        bucket_const_iterator find_entry_for(Key const& key) const {
            return std::find_if(data.begin(), data.end(),
                                [&](bucket_value const &item)
                                { return item.first == key; });
        }

        bucket_iterator find_entry_for(Key const& key) {
            return std::find_if(data.begin(), data.end(),
                                [&](bucket_value const &item)
                                { return item.first == key; });
        }

        Value value_for(Key const& key, Value const& default_value) const {
            std::shared_lock<std::shared_mutex> lock(mut);
            bucket_const_iterator found_entry = find_entry_for(key);
            return (found_entry == data.end()) ?  default_value : found_entry->second;
        }

        void add_or_update_mapping(Key const& key, Value const& value) {
            std::unique_lock<std::shared_mutex> lock(mut);
            bucket_iterator const found_entry = find_entry_for(key);
            if (found_entry == data.end()) {
                data.push_back(bucket_value(key, value));
            } else {
                found_entry->second = value;
            }
        }

        void remove_mapping(Key const& key) {
            std::unique_lock<std::shared_mutex> lock(mut);
            bucket_iterator const found_entry = find_entry_for(key);
            if (found_entry != data.end()) {
                data.erase(found_entry);
            }
        }
    };

    std::vector<std::unique_ptr<bucket_type> > buckets;
    Hash hasher;

    bucket_type& get_bucket(Key const& key) const {
        std::size_t const bucket_index = hasher(key) % buckets.size();
        return *buckets[bucket_index];
    }

public:
    using key_type = Key;
    using mapped_type = Value;
    using hash_type = Hash;

    threadsafe_lookup_table(unsigned num_buckets = 19, Hash const& hasher_ = Hash()):
        buckets(num_buckets), hasher(hasher_) {
        for (unsigned i = 0; i < num_buckets; ++i) {
            buckets[i].reset(new bucket_type);
        }
    }

    threadsafe_lookup_table(threadsafe_lookup_table const& other) = delete;
    threadsafe_lookup_table& operator=(const threadsafe_lookup_table& other) = delete;

    Value value_for(Key const& key,
                    Value const& default_value = Value()) const {
        return get_bucket(key).value_for(key, default_value);
    }

    void add_or_update_mapping(Key const& key, Value const& value) {
        get_bucket(key).add_or_update_mapping(key, value);
    }

    void remove_mapping(Key const& key) {
        get_bucket(key).remove_mapping(key);
    }

    std::map<Key, Value> get_map() const {
        std::vector<std::unique_lock<std::shared_mutex> > locks;
        for (unsigned i = 0; i < buckets.size(); ++i) {
            locks.push_back(
                std::unique_lock<std::shared_mutex>(buckets[i]->mut));
        }
        std::map<Key, Value> res;
        for (unsigned i = 0; i < buckets.size(); ++i) {
            for (typename bucket_type::bucket_iterator it = buckets[i]->data.begin();
                 it != buckets[i]->data.end();
                 ++it) {
                res.insert(*it);
            }
        }
        return res;
    }
};

int main(void)
{
    threadsafe_lookup_table<int, int> table;
    table.add_or_update_mapping(1, 2);
    table.add_or_update_mapping(2, 3);
    std::cout << table.value_for(1) << std::endl;
    std::cout << table.value_for(2) << std::endl;
    auto m = table.get_map();
    std::cout << m[1] << std::endl;
    return 0;
}
