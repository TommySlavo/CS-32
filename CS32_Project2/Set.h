//
//  Set.h
//  CS32_Project2
//
//  Created by Tom Slavonia on 1/24/23.
//

#ifndef Set_h
#define Set_h

#include <string>

using ItemType = unsigned long;

class Set {
public:
    Set();
    Set(const Set& other);
    ~Set();
    Set& operator=(const Set& other);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);
    
private:
    
    struct Node{
        Node* prev;
        Node* next;
        ItemType value;
    };
    
    int m_size;
    Node* head;
    Node* tail;
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void butNot(const Set& s1, const Set& s2, Set& result);


#endif /* Set_h */
