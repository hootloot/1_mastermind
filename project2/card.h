#ifndef CARD_H
#define CARD_H

#include <iostream>

enum Suit { CLUB, DIAMOND, HEART, SPADE };

class card {
private:
    int value;      
    Suit suit;

public:
   
    card() {
        value = 1;
        suit = CLUB;
    }

    card(int v, Suit s) {
        value = v;
        suit = s;
    }

    
    void setValue(int v) {
        value = v;
    }


    void setSuit(Suit s) {
        suit = s;
    }

    int getValue() const {
        return value;
    }

  
    Suit getSuit() const {
        return suit;
    }

   
    friend std::ostream& operator<<(std::ostream& os, const card& c) {

      
        if (c.value == 1)
            os << "Ace";
        else if (c.value == 11)
            os << "Jack";
        else if (c.value == 12)
            os << "Queen";
        else if (c.value == 13)
            os << "King";
        else
            os << c.value;

        os << " of ";

     
        if (c.suit == CLUB)
            os << "Clubs";
        else if (c.suit == DIAMOND)
            os << "Diamonds";
        else if (c.suit == HEART)
            os << "Hearts";
        else if (c.suit == SPADE)
            os << "Spades";

        return os;
    }
};

#endif


#include <iostream>
#include "card.h"

int main() {

    card c1;                    // default (Ace of Clubs)
    card c2(1, SPADE);          // Ace of Spades
    card c3(12, HEART);         // Queen of Hearts
    card c4(7, DIAMOND);        // 7 of Diamonds

    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    std::cout << c3 << std::endl;
    std::cout << c4 << std::endl;

    return 0;
}
