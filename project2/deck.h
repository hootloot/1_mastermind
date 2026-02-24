// File: deck.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Flip cards part a

#ifndef DECK_CLASS
#define DECK_CLASS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "d_node.h"
#include "card.h"

using namespace std;

class deck {
public:
    node<card>* front; // pointer to the first card in the linked list

    // Constructor: creates a full 52-card deck in order
    // goes ace through king for each suit
    // suit order: clubs, diamonds, hearts, spades
    deck() : front(NULL) {
        node<card>* tail = NULL; // keeps track of the end so we can add to the back
        Suit suits[] = { CLUB, DIAMOND, HEART, SPADE };

        // loop through each suit
        for (int s = 0; s < 4; s++) {
            // loop through values 1 (ace) to 13 (king)
            for (int v = 1; v <= 13; v++) {
                // make a new node with this card
                node<card>* newNode = new node<card>(card(v, suits[s]));
                // if the list is empty this is the first node
                if (front == NULL) {
                    front = newNode;
                    tail = newNode;
                    // otherwise add it to the end
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
    }

    // Destructor, goes through the list and deletes every node
    // need this or else we get memory leaks
    ~deck() {
        while (front != NULL) {
            node<card>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // counts how many cards are left in the deck
    // just walks through the whole list and counts
    int size() const {
        int count = 0;
        node<card>* curr = front;
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    // shuffles the deck 
    void shuffle() {
        int n = size();
        if (n <= 1) return;

        // Collect all cards into an temp array
        card* arr = new card[n];
        node<card>* curr = front;
        for (int i = 0; i < n; i++) {
            arr[i] = curr->nodeValue;
            curr = curr->next;
        }

        // start from end, swap each element with a random one at or before it
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1); // random index
            // swap arr[i] and arr[j]
            card temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        // put the shuffled cards back into the linked list nodes
        curr = front;
        for (int i = 0; i < n; i++) {
            curr->nodeValue = arr[i];
            curr = curr->next;
        }

        delete[] arr; // clear temp array
    }

    // deals one card off the top of the deck
    // removes the front node and returns the card that was in it
    card deal() {
        if (front == NULL) {
            return card(); // if empty just return default card
        }
        node<card>* temp = front; // save pointer to front node
        card c = temp->nodeValue; // grab the card value
        front = front->next; // move front to next node
        delete temp; // free old front node
        return c;
    }

    // overload operator to print out whole deck
    friend ostream& operator<<(ostream& os, const deck& d) {
        node<card>* curr = d.front;
        int i = 1;
        while (curr != NULL) {
            os << i << ": " << curr->nodeValue << endl;
            curr = curr->next;
            i++;
        }
        return os;
    }

private:
    // Prevent copying a deck that would mess up the pointers and cause double deletes
    deck(const deck&);
    deck& operator=(const deck&);
};

#endif 