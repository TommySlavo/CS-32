//
//  newSet.h
//  CS_32_Homework_1
//
//  Created by Tom Slavonia on 1/19/23.
//

#ifndef newSet_h
#define newSet_h

#include <string>

const int DEFAULT_MAX_ITEMS = 160;

using ItemType = std::string;

class newSet
{
public:
    newSet();
    
    newSet(int max);
    
    ~newSet();
    
    newSet(const newSet& other);
    
    bool empty() const;
    
    int size() const;
    
    bool insert(const ItemType& value);
    
    bool erase(const ItemType& value);
    
    
    bool contains(const ItemType& value) const;
    
    
    bool get(int i, ItemType& value) const;
    
    
    void swap(newSet& other);
    
    newSet& operator=(const newSet& other);
    
private:
    int m_size;
    int m_max;
    ItemType* m_array; // fix this
    
};

#endif /* newSet_h */
