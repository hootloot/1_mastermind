// File: mastermind.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "code.h"
#include "response.h"

// part b:

class mastermind 
{
    private:
        code secretCode;
        int n;
        int m;

    public:
        mastermind(int length, int range);

        mastermind();

        void printSecretCode() const;

        code humanGuess();

        response getResponse(const code& guess);

        bool isSolved(const response& r);

        void playGame();

    // Person 3 finishes here
    // playGame(), etc

};

#endif
