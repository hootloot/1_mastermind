#ifndef CARD_CLASS
#define CARD_CLASS

#include <iostream>
#include <string>

using namespace std;

enum Suit { CLUB, DIAMOND, HEART, SPADE };

class card {
public:
    card() : value(1), suit(CLUB) {}
    card(int v, Suit s) : value(v), suit(s) {}

    void setValue(int v) { value = v; }
    void setSuit(Suit s) { suit = s; }
    int getValue() const { return value; }
    Suit getSuit() const { return suit; }

    friend ostream& operator<<(ostream& os, const card& c) {
        // Value
        switch (c.value) {
            case 1:  os << "Ace"; break;
            case 11: os << "Jack"; break;
            case 12: os << "Queen"; break;
            case 13: os << "King"; break;
            default: os << c.value; break;
        }
        os << " of ";
        // Suit
        switch (c.suit) {
            case CLUB:    os << "Clubs"; break;
            case DIAMOND: os << "Diamonds"; break;
            case HEART:   os << "Hearts"; break;
            case SPADE:   os << "Spades"; break;
        }
        return os;
    }

private:
    int value;   // 1=Ace, 2-10, 11=Jack, 12=Queen, 13=King
    Suit suit;
};

#endif // CARD_CLASS