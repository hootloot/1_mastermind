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
        code secretCode; // random secret code
        int n; // length of code
        int m; // range of digits

    public:
        mastermind(int length, int range);
        // initializes the game with a code

        mastermind();
        // initalizes the game with default values

        void printSecretCode() const;
        // prints the secret code

        code humanGuess();
        // reads the input and returns a code object representing that guess

        response getResponse(const code& guess);
        // returns a response object containing the count of correct and incorrect

        bool isSolved(const response& r); // returns true if the response was guessed correctly

        void playGame(); 
        // initializes the secret code, then enters a loop asking for guesses

};

#endif
