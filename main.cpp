// File: main.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "mastermind.h"

using namespace std;

// define main function
int main() 
{
    // statement required to generate random values
    srand(time(0));
    int n, m;
    cout << "Please enter the length of your code (1-10): ";
    cin >> n;
    cout << "Enter max digit value (1-10): ";
    cin >> m;

    if (n < 1 || n > 10) 
    {
        cout << "This is Invalid. Since this is Invalid, the value that will be used is 5" << endl;
        n = 5;
    }
    if (m < 1 || m > 10) 
    {
        cout << "This is Invalid. Since this is Invalid, the value that will be used is 10" << endl;
        m = 10;
    }

    mastermind game(n, m);

    game.playGame();
    
    return 0;
}