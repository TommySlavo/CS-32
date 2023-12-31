//
//  CardSet.h
//  CS_32_Homework_1
//
//  Created by Tom Slavonia on 1/19/23.
//

#ifndef CardSet_h
#define CardSet_h

#include "Set.h"
#include <string>


class CardSet
  {
    public:
      CardSet();          // Create an empty card set.

      bool add(ItemType cardNumber);
        // Add a card number to the CardSet.  Return true if and only if the
        // card number was actually added.

      int size() const;  // Return the number of card numbers in the CardSet.

      void print() const;
        // Write to cout every card number in the CardSet exactly once, one
        // per line.  Write no other text.

    private:
      Set m_cardSet;
  };

#endif /* CardSet_h */
