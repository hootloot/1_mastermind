// File: response.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

#include "response.h"
#include <iostream>
using namespace std;

response::response(int c, int i) 
{
    numCorrect = c;
    numIncorrect = i;
}

int response::getCorrect() const 
{ return numCorrect; }

int response::getIncorrect() const 
{ return numIncorrect; }

void response::setCorrect(int c) 
{ numCorrect = c; }

void response::setIncorrect(int i) 
{ numIncorrect = i; }

bool operator==(const response& r1, const response& r2) 
{
    bool sameCorrect = false;
    bool sameIncorrect = false;

    if (r1.getCorrect() == r2.getCorrect()) 
    { sameCorrect = true; }

    if (r1.getIncorrect() == r2.getIncorrect()) 
    { sameIncorrect = true; }

    if (sameCorrect && sameIncorrect) 
    { return true;
    } else 
    { return false; }
}

ostream& operator<<(ostream& out, const response& r) 
{
    out << r.getCorrect();
    out << " correct location, ";
    out << r.getIncorrect();
    out << " incorrect location";
    return out;
}