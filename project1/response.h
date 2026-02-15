// File: response.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B
// This file defines the response class, which represents the 
// feedback provided to a player after they make a guess in the Mastermind game

#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>

using namespace std;

class response 
{
private:
    int numCorrect; // stores the number of correct digit, correct position
    int numIncorrect; // stores the number of correct digit, not incorrect position

public:
    response(int c = 0, int i = 0);
    // initializes the response object

    int getCorrect() const; // accessor function for numCorrect, returns correct

    int getIncorrect() const; // accessor function for numIncorrect

    void setCorrect(int c); // functino to set the number of correct matches

    void setIncorrect(int i); // function set the number of incorrect position matches
};

// overloaded equality operator
// compares two response objects to see if their identifcal
// returns true if both numCorrect and numIncorrect match
bool operator==(const response& r1, const response& r2);

// overloaded stream insertion operator
// allows a response object to be printed directly to an output stream
// typically prints the values of numCorrect and numIncorrect
ostream& operator<<(ostream& out, const response& r);

#endif