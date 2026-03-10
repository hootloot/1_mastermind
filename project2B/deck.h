// File: deck.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Flip cards part b

#ifndef DECK_CLASS
#define DECK_CLASS

#include <iostream>
#include "d_node.h"
#include "card.h"

class deck {
public:
    node<card>* front; // pointer to the first card in the linked list

    // Constructor: creates a full 52-card deck in order
    // goes ace through king for each suit
    // suit order: clubs, diamonds, hearts, spades
    deck(bool makeFullDeck = true);

    // Destructor, goes through the list and deletes every node
    // need this or else we get memory leaks
    ~deck();

    // counts how many cards are left in the deck
    // just walks through the whole list and counts
    int size() const;

    // shuffles the deck
    void shuffle();

    // deals one card off the top of the deck
    // removes the front node and returns the node pointer
    node<card>* deal();

    // places a card node on the bottom of the deck
    void replace(node<card>* c);

    // overload operator to print out whole deck
    friend std::ostream& operator<<(std::ostream& os, const deck& d);

private:
    // Prevent copying a deck that would mess up the pointers and cause double deletes
    deck(const deck&);
    deck& operator=(const deck&);
};

#endif