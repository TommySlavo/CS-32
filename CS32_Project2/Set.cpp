//
//  Set.cpp
//  CS32_Project2
//
//  Created by Tom Slavonia on 1/24/23.
//

#include "Set.h"
#include <string>
#include <iostream>

using ItemType = unsigned long;

Set::Set() {
    m_size = 0;
    head = nullptr;
    tail = nullptr;
}

Set::Set(const Set& other) { // copy constructor
    
    if (other.head == nullptr) { // if the other set is empty
        head = nullptr;
        tail = nullptr;
        m_size = 0;
    }
    else {
        m_size = other.m_size;
    
        head = new Node; // creating first Node
        head->prev = nullptr;
        head->value = other.head->value; 
        Node* p = head; // starts loop at head
        Node* k = other.head->next;
        
        while (k != nullptr) {
            p->next = new Node; //creates new Node right after current Node and points to it
            p->next->value = k->value; // set value of next Node
            p->next->prev = p; // set prev of next Node to current Node
            p = p->next; // iterator
            k = k->next; // iterator
        }
        
        p->next = nullptr;
        tail = p; // sets tail pointer to last Node
    }
}

Set& Set::operator=(const Set& other) {
    
    if (&other == this) { // preventing aliasing
        return(*this);
    }

    Set temp = other; // relies on success of copy constructor
    
    this->swap(temp);
    
    return(*this);
}

Set::~Set() {
    Node* p = head;
    
    while (p != nullptr) {
        Node* n = p->next;
        delete p;
        p = n;
    }
}

bool Set::empty() const {
    if (m_size ==0) {
        return(true);
    }
    
    return(false);
}

int Set::size() const {
    return(m_size);
}

bool Set::insert(const ItemType& value) {
    
    
    if (m_size == 0) {
        Node* p;
        p = new Node;
        p->value = value;
        p->next = nullptr;
        p->prev = nullptr;
        head = p;
        tail = p;
        m_size = m_size + 1;
        return(true);
    }
    else {
        Node* p;
        p = new Node;
        p->value = value;
        p->next = head;
        p->prev = nullptr;
        head->prev = p;
        head = p;
        m_size = m_size + 1;
        return(true);
    }
    
    return(false);
}

bool Set::erase(const ItemType& value) {
    
    if (head == nullptr) {
        return(false);
    }
    
    Node* temp = head;
    
    while (temp != nullptr) {
        if (temp->value == value) {
            if (temp == head && temp == tail) {
                head = nullptr;
                tail = nullptr;
                m_size = m_size - 1;
                delete temp;
                return(true);
            }
            else if (temp == head) {
                head = temp->next;
                m_size = m_size - 1;
                temp->next->prev = nullptr;
                delete temp; 
                return(true);
            }
            else if (temp == tail) {
                tail = temp->prev;
                tail->next = nullptr;
                delete temp;
                m_size = m_size - 1;
                return(true);
            }
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                m_size = m_size - 1;
                return(true);
            }
        }
        
        temp = temp->next;
    }
    
    return(false);
}

bool Set::contains(const ItemType& value) const {
    Node* p = head;
    
    while (p != nullptr) {
        if (p->value == value) {
            return(true);
        }
        
        p = p->next;
    }
    
    return(false);
}

bool Set::get(int i, ItemType& value) const {
    
    if (i < 0 || i >= m_size) {
        return(false);
    }
    
    Node* p = head;
    
    int count = 0;
    
    while (p != nullptr) {
        Node* k = head;
        while (k != nullptr) {
            if (p->value > k->value) {
                count = count + 1;
            }
            k = k->next;
        }
        if (i == count) {
            value = p->value;
            return(true);
        }
        count = 0;
        p = p->next;
    }
    
    return(false);
}

void Set::swap(Set& other) {
    
    int temp_size = other.m_size;
    other.m_size = this->m_size;
    this->m_size = temp_size;
    
    Node* temp_head = other.head;
    other.head = this->head;
    this->head = temp_head;
    
    Node* temp_tail = other.tail;
    other.tail = this->tail;
    this->tail = temp_tail;
    
}

void unite(const Set& s1, const Set& s2, Set& result) { // watch out for aliasing
    // create conditions for if result is empty
    
    bool is_unique = true;
    
    Set temp_result; // empties out result
    
    ItemType x;
    ItemType y;
    ItemType z;
    
    for (int i = 0; i < s1.size(); i++) {
        s1.get(i, x);
        
        temp_result.insert(x); // insert every value in s1
    }
    
    for (int i = 0; i < s2.size(); i++) {
        s2.get(i, y);
        for (int j = 0; j < s1.size(); j++) {
            s1.get(j, z);
            if (y == z) { // if the value is also in s1 then it is already in the result set
                is_unique = false;
                break;
            }
        }
        if (is_unique == true) { // if value is only in s2
            temp_result.insert(y); // insert the value
        }
        is_unique = true; // reset is_unique
    }
    
    result = temp_result;
    
}

void butNot(const Set& s1, const Set& s2, Set& result) { // watch out for aliasing
    
    
    if (&s1 == &s2) { // checks for aliasing
        Set temp;
        result = temp;
        return;
    }
    
    Set temp_result; // empties out set
    
    bool is_unique = true; // tracks if item is unique to s1
    
    ItemType x; // don't initialize cause we don't know type
    ItemType y;
    
    for (int i = 0; i < s1.size(); i++) {
        s1.get(i, x);
        for (int j = 0; j < s2.size(); j++) {
            s2.get(j, y);
            
            if (x == y) { // if the value is in both s1 and s2 it is not unique to s1
                is_unique = false;
                break; // does this break both loops I think it only breaks one
            }
        }
        if (is_unique == true) {
            temp_result.insert(x); // insert only from s1
        }
        is_unique = true; // reset if value is only in s1
    }
    
    result = temp_result;
    
}

