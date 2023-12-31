//
//  newSet.cpp
//  CS_32_Homework_1
//
//  Created by Tom Slavonia on 1/19/23.
//

#include "newSet.h"
#include <iostream>
#include <string>

using ItemType = std::string;

newSet::newSet() {
    m_max = DEFAULT_MAX_ITEMS; // check if I should have max defined in original class
    m_array = new ItemType[m_max];
    m_size = 0;
}

newSet::newSet(int max) { // fix this
    m_max = max;
    m_array = new ItemType[m_max];
    m_size = 0;
}

newSet::~newSet() {
    delete [] m_array;
}

newSet::newSet(const newSet& other) {
    m_size = other.m_size;
    m_max = other.m_max;
    
    m_array = new ItemType[m_max];
    
    for (int i = 0; i < m_size; i++) {
        m_array[i] = other.m_array[i];
    }

}

newSet& newSet::operator=(const newSet& other) {
    
    if (this == &other) {
        return(*this);
    }
    
    newSet temp = other;
    
    swap(temp);
    
    return(*this);
}


bool newSet::empty() const {
    if (m_size == 0) {
        return(true);
    }
    
    return(false);
}


int newSet::size() const {
    return(m_size);
}


bool newSet::insert(const ItemType& value){
    
    if (m_size == m_max) {
        return(false);
    }
    
    for (int i = 0; i < m_size; i++) {
        if (value == m_array[i]) {
            return(false);
        }
    }
    
    m_array[m_size] = value;
    
    m_size = m_size + 1;
    
    return(true);
}


bool newSet::erase(const ItemType& value) { // fix this
    
    if (m_size == 0) {
        return(false);
    }
    
    for (int i = 0; i < m_size; i++) {
        if (m_array[i] == value) {
            for (int j = i; j < m_size - 1; j++) {
                m_array[j] = m_array[j + 1];
            }
            m_size = m_size - 1;
            return(true);
        }
    }
    
    return(false);
}


bool newSet::contains(const ItemType& value) const {
    
    if (m_size == false) {
        return(false);
    }
    
    for(int i = 0; i < m_size; i++) {
        if (m_array[i] == value) {
            return(true);
        }
    }
    
    return(false);
}


bool newSet::get(int i, ItemType& value) const {
    
    if (i < 0 || i > m_size) {
        return(false);
    }
    
    int count = 0;
    
    
    for (int k = 0; k < m_size; k++) {
        for (int j = 0; j < m_size; j++) {
            if (m_array[k] > m_array[j]) {
                count = count + 1;
            }
        }
        if (count == i) {
            value = m_array[k];
            return(true);
        }
        count = 0;
    }
    
    return(false);
}


void newSet::swap(newSet& other) { // fix this
    
    int temp_max = other.m_max;
    other.m_max = this->m_max;
    this->m_max = temp_max;
    
    int max;
    
    if (this->m_size > other.m_size) {
        max = this->m_size;
    }
    else {
        max = other.m_size;
    }
    
    ItemType* temp_array = new ItemType[max];
    
    for (int i = 0; i < other.m_size; i++) {
        temp_array[i] = other.m_array[i];
    }
    
    for (int i = 0; i < m_size; i++) {
        other.m_array[i] = this->m_array[i];
    }
    
    for (int i = 0; i < other.m_size; i++) {
        this->m_array[i] = temp_array[i];
    }
    
    int temp_size = other.m_size;
    other.m_size = this->m_size;
    this->m_size = temp_size;
    
    delete [] temp_array;
    
    
}
