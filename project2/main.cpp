#include <iostream>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "deck.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0)));

    deck myDeck;

    // Print deck before shuffling
    cout << "=== Deck Before Shuffle ===" << endl;
    cout << myDeck << endl;

    // Shuffle three times
    myDeck.shuffle();
    myDeck.shuffle();
    myDeck.shuffle();

    // Print deck after shuffling
    cout << "=== Deck After Shuffle ===" << endl;
    cout << myDeck << endl;

    // --- Game: Flip ---
    // Draw 24 cards face down
    card table[24];
    bool faceUp[24] = { false };
    for (int i = 0; i < 24; i++) {
        table[i] = myDeck.deal();
    }

    double score = 0.0;
    int flipped = 0;

    cout << "=== Welcome to Flip! ===" << endl;

    while (true) {
        // Display the 24 cards (face-down or revealed)
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

        // Check if all cards are flipped
        if (flipped == 24) {
            cout << "All cards have been flipped!" << endl;
            break;
        }

        cout << "Enter a card number (1-24) to flip, or 0 to end the game: ";
        int choice;
        cin >> choice;

        if (choice == 0) break;

        if (choice < 1 || choice > 24) {
            cout << "Invalid choice. Try again." << endl;
            continue;
        }

        int idx = choice - 1;
        if (faceUp[idx]) {
            cout << "That card is already flipped. Choose another." << endl;
            continue;
        }

        // Flip the card
        faceUp[idx] = true;
        flipped++;
        card c = table[idx];
        cout << "You flipped: " << c << endl;

        int v = c.getValue();
        Suit s = c.getSuit();

        // Apply scoring rules
        if (v == 1) {              // Ace
            score += 10;
            cout << "  +10 points (Ace)" << endl;
        } else if (v >= 11) {     // Jack, Queen, King
            score += 5;
            cout << "  +5 points (Face card)" << endl;
        } else if (v >= 8 && v <= 10) {
            cout << "  +0 points (8, 9, or 10)" << endl;
        } else if (v == 7) {
            score /= 2.0;
            cout << "  Lost half your points! (7)" << endl;
        } else {                   // 2-6
            score = 0;
            cout << "  Lost ALL your points! (" << v << ")" << endl;
        }

        // Bonus for hearts
        if (s == HEART) {
            score += 1;
            cout << "  +1 bonus point (Heart)" << endl;
        }
    }

    cout << "\n=== Game Over ===" << endl;
    cout << "Final Score: " << score << endl;

    return 0;
}