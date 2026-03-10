// File: card.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Flip cards part b

#include "card.h"

// default constructor, thus makes ace of clubs
card::card() : value(1), suit(CLUB) {}

// constructor with value and suit
card::card(int v, Suit s) : value(v), suit(s) {}

// copy constructor
card::card(const card& other) {
    value = other.value;
    suit = other.suit;
}

// overloaded assignment operator
card& card::operator=(const card& other) {
    if (this != &other) {
        value = other.value;
        suit = other.suit;
    }
    return *this;
}

// setters
void card::setValue(int v) { value = v; }

void card::setSuit(Suit s) { suit = s; }

// getter functions
int card::getValue() const { return value; }

Suit card::getSuit() const { return suit; }

// prints card like "Ace of spades, etc"
std::ostream& operator<<(std::ostream& os, const card& c) {
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