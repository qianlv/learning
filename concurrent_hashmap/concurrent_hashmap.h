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
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CONCURRENT_HASHMAP_H
#define CONCURRENT_HASHMAP_H

#include <vector>

template <typename KeyType, typename ValueType>
struct Entry
{
    Entry(KeyType key, ValueType val)
    {
        next_ = nullptr;
        key_ = key;
        val_ = val;
    }
    struct Entry *next_;
    ValueType val_;
    KeyType key_;
};

template <typename KeyType, typename ValueType, typename Hash = std::hash<std::size_t>, int MAX_ENTRY_NUM = 16>
struct Segment
{
    using entryType= Entry<KeyType, ValueType>;
    entryType *entrys_[MAX_ENTRY_NUM] = {nullptr};
    static constexpr int entryCount = MAX_ENTRY_NUM;
    void insert(KeyType key, ValueType val, std::size_t keyHashVal)
    {
        int index = Hash(keyHashVal) & (entryCount - 1);
        entryType *entry = new entryType(key, val);
        if (entrys_[index] == nullptr) 
        {
            entrys_[index] = entry;
        }
        else
        {
            entry->next = entrys_[index];
            entrys_[index] = entry;
        }
    }
};

template <typename KeyType, typename ValueType, typename Hash = std::hash<KeyType>, int MAX_SEGMENTS_NUM = 16>
class ConcurrentHashmap
{
public:
    ConcurrentHashmap();
    virtual ~ConcurrentHashmap();
private:
    Segment<KeyType, ValueType> segments_[MAX_SEGMENTS_NUM];
    static constexpr int segmentCount = MAX_SEGMENTS_NUM;
};

#endif /* CONCURRENT_HASHMAP_H */
