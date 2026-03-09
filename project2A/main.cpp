// File: main.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Flip cards part a

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "deck.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0))); // seed random

    deck myDeck;

    // prints deck before shuffling
    cout << "Deck Before Shuffle" << endl;
    cout << myDeck << endl;

    // shuffle 3 times
    myDeck.shuffle();
    myDeck.shuffle();
    myDeck.shuffle();

    // prints deck after shuffling
    cout << "Deck After Shuffle" << endl;
    cout << myDeck << endl;

    
    // Draw 24 cards face down
    card table[24];
    bool faceUp[24] = { false }; // keeps track of which cards have been flipped
    for (int i = 0; i < 24; i++) {
        table[i] = myDeck.deal();
    }

    double score = 0.0;
    int flipped = 0;

    cout << "Welcome to Flip!" << endl;

    while (true) {
        // show all 24 cards, ??? if face dow
        cout << "\nYour cards:" << endl;
        for (int i = 0; i < 24; i++) {
            cout << "  [" << (i + 1) << "] ";
            if (faceUp[i])
                cout << table[i] << " (flipped)";
            else
                cout << "???";
            cout << endl;
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

        // check if already flipped
        if (faceUp[idx]) {
            cout << "That card is already flipped. Choose another." << endl;
            continue;
        }

        // Flip the card and output it
        faceUp[idx] = true;
        flipped++;
        card c = table[idx];
        cout << "You flipped: " << c << endl;

        int v = c.getValue();
        Suit s = c.getSuit();

        // apply the scoring rules
        if (v == 1) {              // Ace
            score += 10;
            cout << "  +10 (Ace)" << endl;
        } else if (v >= 11) {     // Jack, Queen, King, face cards
            score += 5;
            cout << "  +5 (Face card)" << endl;
        } else if (v >= 8 && v <= 10) { // 8 - 10 = nothing
            cout << "  +0 (8, 9, or 10)" << endl;
        } else if (v == 7) { // 7, lose half
            score /= 2.0;
            cout << "  Lost half your points (7)" << endl;
        } else {                   // 2-6, lose everything
            score = 0;
            cout << "  Lost all your points (" << v << ")" << endl;
        }

        // hearts give a bonus point on top of whatever else happed
        if (s == HEART) {
            score += 1;
            cout << "  +1 bonus (Heart)" << endl;
        }
    }

    cout << "\nGame Over" << endl;
    cout << "Final Score: " << score << endl;

    return 0;
}