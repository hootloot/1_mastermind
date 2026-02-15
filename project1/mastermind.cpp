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

// Determines whether the most recent response indicates the code is solved.
// Take a response object "r" and returns a boolean depending on if the user guessed correctly.
bool mastermind::isSolved(const response& r) 
{
	// The game is solved when every position is correct.
    if (r.getCorrect() == secretCode.length()) {
        return true;
    }

    return false;
}

// Runs one full game of Mastermind with up to 10 guesses.
void mastermind::playGame() 
{
	// Initialize the secret code for a new game.
    secretCode.initializeRandom();

	// For testing and grading. Prints the secret code to the user.
    printSecretCode();

	// Run up to 10 rounds of guessing.
    for (int i = 0; i < 10; i++) {
		// Get the human's guess, evaluate it, and print the response.
        response r = getResponse(humanGuess());
        cout << r <<endl;

		// Check for a win after each guess
        if (isSolved(r)) {
            cout << "You win!" <<endl;
            return;
        }
    }

	// If the loop is exited, the player did not solve the code in 10 tries.
    cout << "You lost" << endl;
}