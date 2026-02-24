// File: card.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Flip cards part a

#ifndef CARD_H
#define CARD_H

#include <iostream>

enum Suit { CLUB, DIAMOND, HEART, SPADE };

// suits for the cards
class card {
private:
    int value; // 1 = ace, 2-10 = number, 11 = jack, 12 = queen, 13 = king 
    Suit suit;

public:
   // default construcor, thus makes ace of clubs
    card() {
        value = 1;
        suit = CLUB;
    }

    // constructor with value and suit
    card(int v, Suit s) {
        value = v;
        suit = s;
    }

    // setters
    void setValue(int v) {
        value = v;
    }


    void setSuit(Suit s) {
        suit = s;
    }

    // getter functions
    int getValue() const {
        return value;
    }

  
    Suit getSuit() const {
        return suit;
    }

   // prints card like "Ace of spades, etc"
    friend std::ostream& operator<<(std::ostream& os, const card& c) {

        // print name for face cards, otherwise just the number
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

        // print suit name
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



