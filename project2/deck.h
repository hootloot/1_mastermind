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
    node<card>* front;

    // Constructor: creates a full 52-card deck in order
    // Ace through King, Clubs then Diamonds then Hearts then Spades
    deck() : front(NULL) {
        node<card>* tail = NULL;
        Suit suits[] = { CLUB, DIAMOND, HEART, SPADE };
        for (int s = 0; s < 4; s++) {
            for (int v = 1; v <= 13; v++) {
                node<card>* newNode = new node<card>(card(v, suits[s]));
                if (front == NULL) {
                    front = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
    }

    // Destructor
    ~deck() {
        while (front != NULL) {
            node<card>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Returns the number of cards currently in the deck
    int size() const {
        int count = 0;
        node<card>* curr = front;
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    // Shuffle: convert list to array, Fisher-Yates shuffle, rebuild list
    void shuffle() {
        int n = size();
        if (n <= 1) return;

        // Collect all cards into an array
        card* arr = new card[n];
        node<card>* curr = front;
        for (int i = 0; i < n; i++) {
            arr[i] = curr->nodeValue;
            curr = curr->next;
        }

        // Fisher-Yates shuffle
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            card temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        // Put shuffled cards back into the linked list
        curr = front;
        for (int i = 0; i < n; i++) {
            curr->nodeValue = arr[i];
            curr = curr->next;
        }

        delete[] arr;
    }

    // Deal (remove and return) the top card from the deck
    card deal() {
        if (front == NULL) {
            return card(); // fallback
        }
        node<card>* temp = front;
        card c = temp->nodeValue;
        front = front->next;
        delete temp;
        return c;
    }

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
    // Prevent copying
    deck(const deck&);
    deck& operator=(const deck&);
};

#endif // DECK_CLASS