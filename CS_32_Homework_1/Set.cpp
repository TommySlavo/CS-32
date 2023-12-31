//
//  Set.cpp
//  CS_32_Homework_1
//
//  Created by Tom Slavonia on 1/19/23.
//

#include "Set.h"
#include <iostream>
#include <string>

using ItemType = std::string;

Set::Set() {
    m_size = 0;
}


bool Set::empty() const {
    if (m_size == 0) {
        return(true);
    }
    
    return(false);
}


int Set::size() const {
    return(m_size);
}


bool Set::insert(const ItemType& value){
    
    if (m_size == DEFAULT_MAX_ITEMS) { // don't add another item if max has been reached
        return(false);
    }
    
    for (int i = 0; i < m_size; i++) {
        if (value == m_array[i]) { // don't add item if the item is already in the set
            return(false);
        }
    }
    
    m_array[m_size] = value; // places item right after end of array
    
    m_size = m_size + 1; // increments the size to account for the new item
    
    return(true);
}


bool Set::erase(const ItemType& value) {
    
    if (m_size == 0) { // can't get rid of an item if there are no items
        return(false);
    }
    
    for (int i = 0; i < m_size; i++) {
        if (m_array[i] == value) { // if we've found value we want to erase
            for (int j = i; j < m_size - 1; j++) { // this moves every value above the erased value down by one
                m_array[j] = m_array[j + 1]; // technically an item will still exist where it shouldn't but decrementing size removes that problem
            }
            m_size = m_size - 1; // decrements size
            return(true);
        }
    }
    
    return(false);
}


bool Set::contains(const ItemType& value) const {
    
    if (m_size == 0) { // if size is 0 the item is obviously not in the array
        return(false);
    }
    
    for(int i = 0; i < m_size; i++) {
        if (m_array[i] == value) { // found it
            return(true);
        }
    }
    
    return(false);
}


bool Set::get(int i, ItemType& value) const {
    
    if (i < 0 || i >= m_size) { // if the index is invalid return false
        return(false);
    }
    
    int count = 0; // tracks how many values are greater than our input
    
    
    for (int k = 0; k < m_size; k++) {
        for (int j = 0; j < m_size; j++) {
            if (m_array[k] > m_array[j]) { // if we've found a value greater than input
                count = count + 1; // increment count
            }
        }
        if (count == i) { // if we've found the right number of values greater
            value = m_array[k]; // set value to the correct value
            return(true);
        }
        count = 0; // reset count
    }
    
    return(false); // just incase but this should never be called
}


void Set::swap(Set& other) {
    
    ItemType temp_array[DEFAULT_MAX_ITEMS]; // need temporary array
    
    for (int i = 0; i < other.m_size; i++) {
        temp_array[i] = other.m_array[i]; // copy other array to temporary array
    }
    
    for (int i = 0; i < m_size; i++) {
        other.m_array[i] = m_array[i]; // set our other array to this array
    }
    
    for (int i = 0; i < other.m_size; i++) {
        m_array[i] = temp_array[i]; // set this array to the copy
    }
    
    int temp_size = other.m_size; // reseting sizes
    other.m_size = m_size;
    m_size = temp_size;
    
}


