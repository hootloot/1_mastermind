// File: main.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Mastermind Part B

// the first include statement is assigned to a vector
//the statements below (the include statements) utilize the libaries
// to make the code function
#include <vector>
#include <cstdlib>
#include <ctime>
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
    code(int length, int range) 
    {
        // assigned the length and range to variables n and m
        // implemented the resize function in order to add more numbers to the range
        n = length;
        m = range;
        content.resize(n);
    }
    // created a function to generate random values for the code
    void initializeRandom() 
    {
        // the for statement goes through each part in the code
        for (int i = 0; i < n; i++) {
            //created the statement to assign a random number to the range
            content[i] = rand() % m;
        }
    }

    // created a function called readGuess to implement the user to guess the number
    void readGuess() 
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
    void print() const 
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
    void setGuess(const vector<int>& digits) {
        if (digits.size() == n) {
            content = digits;
        }
    }

    // the statement returns the length of the code
    int length() const { return n; }

    // this statement returns the value of the number at a specific position
    int digitAt(int i) const { return content[i]; }

   //implemented function to check if digits are correct but in the wrong position
    int checkIncorrect(const code& guess) const {
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
    int checkCorrect(const code& guess) const 
    {

        int correct = 0;
        for (int i=0; i < n; i++) {
            if (digitAt(i) == guess.digitAt(i)) {
                correct++;
            }
        }
        return correct;

    }


};

class response 
{
private:
    int numCorrect;
    int numIncorrect;

public:
    response(int c = 0, int i = 0) 
    {
        numCorrect = c;
        numIncorrect = i;
    }

    int getCorrect() const 
    { return numCorrect; }

    int getIncorrect() const 
    { return numIncorrect; }

    void setCorrect(int c) 
    { numCorrect = c; }

    void setIncorrect(int i) 
    { numIncorrect = i; }
};

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




// part b:


class mastermind 
{
    private:
        code secretCode;
        int n;
        int m;

    public:
        mastermind(int length, int range) : secretCode(length, range) 
        {
            n = length;
            m = range;
        }

    mastermind() : secretCode(5, 10) 
    {
        n = 5;
        m = 10;
    }

    void printSecretCode() const 
    {
        secretCode.print();
    }

    code humanGuess() 
    {
        code guess(n, m);
        guess.readGuess();
        return guess;
    }

    response getResponse(const code& guess) 
    {
        int correct = secretCode.checkCorrect(guess);
        int incorrect = secretCode.checkIncorrect(guess);
        return response(correct, incorrect);
    }
    bool isSolved(const response& r) 
    {
            if (r.getCorrect() == secretCode.length()) {
                return true;
            }
            return false;
        }
    void playGame() 
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

    // Person 3 finishes here
    // playGame(), etc

};


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
