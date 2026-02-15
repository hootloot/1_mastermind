// File: code.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

#ifndef CODE_H
#define CODE_H

//implemented the vector library in order contain the digits for the code
#include <vector>
#include <iostream>

//this statement uses the namespace in order for library names such as
// cout, cin, for print statements to displays the outputs of the code
using namespace std;

// the class code is defined
// the class code contains a series of multiple numbers
class code 
{
private:

//implemented the vector library in order contain the digits for the code
    vector<int> content;
// defined n to represent the length of the code and m to represent the range
// of the series of numbers
    int n;
    int m;

public:

// defined an object called code to contain the length and range within parameters
    code(int length, int range);

    // created a function to generate random values for the code
    void initializeRandom();

    // created a function called readGuess to implement the user to guess the number
    void readGuess();

    // this function will print the output of the code
    void print() const;

    // function for the last requirement, where we have to test specific codes
    // accepts a vector, and set it to the code
    void setGuess(const vector<int>& digits);

    // the statement returns the length of the code
    int length() const;

    // this statement returns the value of the number at a specific position
    int digitAt(int i) const;

   //implemented function to check if digits are correct but in the wrong position
    int checkIncorrect(const code& guess) const;

    //Similar to the function of the checkIncorrect function
    // the checkCorrect Function applies a similar foundation for the logic but except
    // the function is going to count how many digits match
    int checkCorrect(const code& guess) const;
};

#endif