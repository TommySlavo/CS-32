//
//  CardSet.cpp
//  CS_32_Homework_1
//
//  Created by Tom Slavonia on 1/19/23.
//

#include "Set.h"
#include "CardSet.h"
#include <string>

CardSet::CardSet() {
   
}

bool CardSet::add(ItemType cardNumber) {
    
    return(m_cardSet.insert(cardNumber));
}

int CardSet::size() const {
    return(m_cardSet.size());
}

void CardSet::print() const {
    
    for (int i = 0; i < m_cardSet.size(); i++) {
        ItemType value;
        m_cardSet.get(i, value); // all values will be printed
        std::cout << value << std::endl;
    }
}


