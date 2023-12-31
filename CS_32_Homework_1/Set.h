//
//  Set.h
//  CS_32_Homework_1
//
//  Created by Tom Slavonia on 1/19/23.
//

#ifndef Set_h
#define Set_h

#include <iostream>
#include <string>

const int DEFAULT_MAX_ITEMS = 160;

using ItemType = std::string;

class Set
{
public:
    Set();
    bool empty() const;
    
    int size() const;
    
    bool insert(const ItemType& value);
    
    bool erase(const ItemType& value);
    
    
    bool contains(const ItemType& value) const;
    
    
    bool get(int i, ItemType& value) const;
    
    
    void swap(Set& other);
    
private:
    int m_size;
    ItemType m_array[DEFAULT_MAX_ITEMS];
    
};

#endif /* Set_h */
