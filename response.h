// File: response.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>

using namespace std;

class response 
{
private:
    int numCorrect;
    int numIncorrect;

public:
    response(int c = 0, int i = 0);

    int getCorrect() const;

    int getIncorrect() const;

    void setCorrect(int c);

    void setIncorrect(int i);
};

bool operator==(const response& r1, const response& r2);

ostream& operator<<(ostream& out, const response& r);

#endif