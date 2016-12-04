/*
 * =====================================================================================
 *
 *       Filename:  concurrent_hashmap.h
 *
 *    Description:  concurrent HashMap
 *
 *        Version:  1.0
 *        Created:  11/30/2016 10:06:50 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv
 *   Organization:  
 *          Email:  qianlv7 at qq com
 *
 * =====================================================================================
 */

#ifndef CONCURRENT_HASHMAP_H
#define CONCURRENT_HASHMAP_H

#include <vector>
#include <exception>
#include <memory>
#include <forward_list>
#include <list>

template <typename KeyType, typename ValueType>
struct Entry
{
    Entry(KeyType key, ValueType val)
    {
        key_ = key;
        val_ = val;
    }
    ValueType val_;
    KeyType key_;
};

template <typename KeyType, typename ValueType>
class Segment
{
    using EntryType = Entry<KeyType, ValueType>;
    using EntryPtrType = std::shared_ptr<EntryType>;
    using ListEntryType = std::forward_list<EntryPtrType>;
public:
    Segment(int cap, float loadFactor)
        : entrys_(cap), loadFactor_(loadFactor), threshold_(cap * loadFactor), entryCount_(0)
    {
    }
    ~Segment() {};

    bool insert(KeyType key, ValueType value, std::size_t hashVal)
    {
        if (entryCount_ > threshold_)
            rehash();
        int index = hashVal & (entrys_.size());
        ListEntryType listEntry = entrys_[index];
        for (const auto& iter : listEntry) {
            if (iter->key_ == key) {
                return false;
            }
        }

        listEntry.push_front(std::make_shared<EntryType>(key, value));
        ++entryCount_;
    }

    EntryType get(KeyType key, std::size_t hashVal)
    {
        int index = hashVal & (entrys_.size());
        ListEntryType listEntry = entrys_[index];
        for (const auto& iter : listEntry) {
            if (iter->key_ == key) {
                return *iter;
            }
        }
    }

    void rehash() {}

private:
    std::vector<ListEntryType> entrys_;
    float loadFactor_;
    int threshold_;
    int entryCount_;
};

template <typename KeyType, typename ValueType, typename Hash = std::hash<KeyType>>
class ConcurrentHashmap
{
    using EntryType = Entry<KeyType, ValueType>;
    using SegmentType = Segment<KeyType, ValueType>;
public:
    ConcurrentHashmap() : 
        ConcurrentHashmap(DEFAULT_INITIAL_CAPACITY, DEFAULT_CONCURRENCY_LEVEL, DEFAULT_LOAD_FACTOR) {};
    ConcurrentHashmap(int initCap, int concurrencyLevel, float loadFactor)
    {
        if (initCap < 0 or concurrencyLevel < 0 or !(loadFactor > 0))
            throw std::exception();

        if (concurrencyLevel > MAX_SEGMENTS)
            concurrencyLevel = MAX_SEGMENTS;

        // 用于hashVal 的高位的值确定位于 segemnts 数组的位置.
        int sshift = 0;
        int segementSize = 1;
        for (; segementSize < concurrencyLevel; ++sshift)
            segementSize <<= 1;
        segmentShift_ = sizeof(std::size_t) - sshift; 
        segmentMask_ = segementSize - 1;

        if (initCap > MAX_CAPACITY)
            initCap = MAX_CAPACITY;
        int cap = (initCap + segementSize - 1) & (~(segementSize - 1)); // 除以 segementSize, 向上取整

        int segmentCap = 1;
        while (segmentCap < cap)
            segmentCap <<= 1;
        for (int i = 0; i < segementSize; ++i) {
            segments_.push_back(SegmentType(segmentCap, loadFactor));
        }
    }
    ~ConcurrentHashmap() {};

    bool insert(KeyType key, ValueType value)
    {
        std::size_t hashVal = Hash()(key);
        return segments_[(hashVal >> segmentShift_) & segmentMask_].insert(key, value, hashVal);
    }

    EntryType get(KeyType key)
    {
        std::size_t hashVal = Hash()(key);
        return segments_[(hashVal >> segmentShift_) & segmentMask_].get(key, hashVal);
    }

private:
    static constexpr int    DEFAULT_INITIAL_CAPACITY    = 16;
    static constexpr int    DEFAULT_CONCURRENCY_LEVEL   = 16;
    static constexpr float  DEFAULT_LOAD_FACTOR         = 0.75f;
    static constexpr int    MAX_SEGMENTS                = (1 << 16);
    static constexpr int    MAX_CAPACITY                = (1 << 16);

    int segmentShift_;
    int segmentMask_;
    std::vector<SegmentType> segments_;
};

#endif /* CONCURRENT_HASHMAP_H */
