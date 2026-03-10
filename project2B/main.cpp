// File: main.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Flip cards part b

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "deck.h"

using namespace std;

// global function that runs the entire flip game
void playFlip() {
    // initialize a deck with 52 cards in order
    deck myDeck;

    // shuffle the deck and print all cards after shuffle
    myDeck.shuffle();
    myDeck.shuffle();
    myDeck.shuffle();
    cout << "Deck after shuffle:" << endl;
    cout << myDeck << endl;

    // draw the top 24 cards from the deck and insert into the hand deck
    // first we need an empty hand deck, so we create one and clear it
    deck hand(false);

    // deal 24 cards from the main deck and place them in the hand
    for (int i = 0; i < 24; i++) {
        hand.replace(myDeck.deal());
    }

    // print the hand deck and the remaining cards in the main deck
    cout << "Hand deck (24 cards):" << endl;
    cout << hand << endl;

    cout << "Remaining deck (" << myDeck.size() << " cards):" << endl;
    cout << myDeck << endl;

    // start the game
    // keep track of which cards have been flipped
    bool faceUp[24] = { false };
    double score = 0.0;
    int flipped = 0;

    cout << "Welcome to Flip!" << endl;

    while (true) {
        // show all 24 cards, ??? if face down
        cout << "\nYour cards:" << endl;
        node<card>* curr = hand.front;
        for (int i = 0; i < 24; i++) {
            cout << "  [" << (i + 1) << "] ";
            if (faceUp[i])
                cout << curr->nodeValue << " (flipped)";
            else
                cout << "???";
            cout << endl;
            curr = curr->next;
        }
        cout << "\nScore: " << score << "  |  Cards flipped: " << flipped << "/24" << endl;

        // if everything is flipped we're done
        if (flipped == 24) {
            cout << "All cards have been flipped!" << endl;
            break;
        }

        // ask player to pick a card or end game
        cout << "Enter a card number (1-24) to flip, or 0 to end the game: ";
        int choice;
        cin >> choice;

        if (choice == 0) break;

        // make sure the input is a valid choice
        if (choice < 1 || choice > 24) {
            cout << "Invalid choice. Try again." << endl;
            continue;
        }

        int idx = choice - 1;

        // bonus: each card can only be flipped once
        if (faceUp[idx]) {
            cout << "That card is already flipped. Choose another." << endl;
            continue;
        }

        // flip the card
        faceUp[idx] = true;
        flipped++;

        // walk to the chosen card in the linked list
        curr = hand.front;
        for (int i = 0; i < idx; i++) {
            curr = curr->next;
        }

        card c = curr->nodeValue;
        cout << "You flipped: " << c << endl;

        int v = c.getValue();
        Suit s = c.getSuit();

        // apply the scoring rules
        if (v == 1) {              // Ace
            score += 10;
            cout << "  +10 (Ace)" << endl;
        } else if (v >= 11) {     // Jack, Queen, King face cards
            score += 5;
            cout << "  +5 (Face card)" << endl;
        } else if (v >= 8 && v <= 10) { // 8-10 = nothing
            cout << "  +0 (8, 9, or 10)" << endl;
        } else if (v == 7) { // 7, lose half
            score /= 2.0;
            cout << "  Lost half your points (7)" << endl;
        } else {                   // 2-6, lose everything
            score = 0;
            cout << "  Lost all your points (" << v << ")" << endl;
        }

        // hearts give a bonus point on top of whatever else happened
        if (s == HEART) {
            score += 1;
            cout << "  +1 bonus (Heart)" << endl;
        }
    }

    cout << "\nGame Over!" << endl;
    cout << "Final Score: " << score << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0))); // seed random

    playFlip();

    return 0;
}