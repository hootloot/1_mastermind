// File: code.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

#include "code.h"
#include <cstdlib>

// defined an object called code to contain the length and range within parameters
code::code(int length, int range) 
{
    // assigned the length and range to variables n and m
    // implemented the resize function in order to add more numbers to the range
    n = length;
    m = range;
    content.resize(n);
}

// created a function to generate random values for the code
void code::initializeRandom() 
{
    // the for statement goes through each part in the code
    for (int i = 0; i < n; i++) {
        //created the statement to assign a random number to the range
        content[i] = rand() % m;
    }
}

// created a function called readGuess to implement the user to guess the number
void code::readGuess() 
{
    // create a user input for guests to input their guests
    cout << "Enter guess (ex: 2 3 4 5 6): ";
      // the for statement goes through each part in the code
    for (int i = 0; i < n; i++) {
        // this statements stores the input value
        cin >> content[i];
    }
}

// this function will print the output of the code
void code::print() const 
{
    // the for statement goes through each part in the code
    for (int i = 0; i < n; i++) {
        // the statement below implements the digit as per the rules and the comma
        cout << content[i] << (i < n - 1 ? ", " : "");
    }

    cout << endl;
}

// function for the last requirement, where we have to test specific codes
// accepts a vector, and set it to the code
void code::setGuess(const vector<int>& digits) {
    if (digits.size() == n) {
        content = digits;
    }
}

// the statement returns the length of the code
int code::length() const { return n; }

// this statement returns the value of the number at a specific position
int code::digitAt(int i) const { return content[i]; }

//implemented function to check if digits are correct but in the wrong position
int code::checkIncorrect(const code& guess) const {
    // this vector statement identifies which secret digits have been used
    vector<bool> usedSecret(n, false);
    // this vector statement identifies which guess digits have been used
    vector<bool> usedGuess(n, false);

    // the for statement goes through each part in the code
    for (int i = 0; i < n; i++) 
    {

        // the if statement compares the secret sequence and the guess
        if (digitAt(i) == guess.digitAt(i)) {
            usedSecret[i] = true;
            usedGuess[i] = true;
        }
    }

    // this statements initailize incorrect to be set to 0
    int incorrect = 0;
    // the for statement goes through each part in the code
    for (int i = 0; i < n; i++) 
    {
        // if the guessed number matches the secret number, then the next number will be checked
        if (usedGuess[i]) continue;
                // the for statement goes through each part in the code
        for (int j = 0; j < n; j++) 
        {
            // if the guessed number matches the secret number, then the next number will be checked
            if (usedSecret[j]) continue;
            // created an if statement to identify if the guess number matches the secret number
            if (guess.digitAt(i) == digitAt(j)) 
            {

                // the number will be considered correct if it is in the wrong location
                incorrect++;

                // the secret number will be marked as already used so when analyzing other sequences, the
                // secret number will not be used again
                usedSecret[j] = true;

                // finish checking the numbers and proceed using break
                break;
            }
        }
    }
    // this statement will return the total number of incorrect-position matches
    return incorrect;
}

//Similar to the function of the checkIncorrect function
// the checkCorrect Function applies a similar foundation for the logic but except
// the function is going to count how many digits match
int code::checkCorrect(const code& guess) const 
{

    int correct = 0;
    for (int i=0; i < n; i++) {
        if (digitAt(i) == guess.digitAt(i)) {
            correct++;
        }
    }
    return correct;

}