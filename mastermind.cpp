// File: mastermind.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

#include "mastermind.h"
#include <iostream>
using namespace std;

mastermind::mastermind(int length, int range) : secretCode(length, range) 
{
    n = length;
    m = range;
}

mastermind::mastermind() : secretCode(5, 10) 
{
    n = 5;
    m = 10;
}

void mastermind::printSecretCode() const 
{
    secretCode.print();
}

code mastermind::humanGuess() 
{
    code guess(n, m);
    guess.readGuess();
    return guess;
}

response mastermind::getResponse(const code& guess) 
{
    int correct = secretCode.checkCorrect(guess);
    int incorrect = secretCode.checkIncorrect(guess);
    return response(correct, incorrect);
}

bool mastermind::isSolved(const response& r) 
{
    if (r.getCorrect() == secretCode.length()) {
        return true;
    }
    return false;
}

void mastermind::playGame() 
{
    /*cout << "Please enter the length of the number you would like to guess, "
            "then enter the maximum digit you would like the digits of the number"
            "to be set to."<< endl;
    cin >> n;
    cin >> m;*/
    secretCode.initializeRandom();
    printSecretCode();
    response Response;
    for (int i = 0; i < 10; i++) {
        Response = getResponse(humanGuess());
        cout << Response <<endl;
        if (isSolved(Response)) {
            cout << "You win!" <<endl;
            return;
        }
    }
    cout<<"You lost"<<endl;
}