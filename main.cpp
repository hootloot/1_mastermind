//the first include statement is assigned to a vector 
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
class code {
private:

//implemented the vector library in order contain the digits for the code
    vector<int> content;
// defined n to represent the length of the code and m to represent the range 
// of the series of numbers
    int n;
    int m;

public:

// defined an object called code to contain the length and range within parameters 
    code(int length, int range) {
        // assigned the length and range to variables n and m 
        // implemented the resize function in order to add more numbers to the range
        n = length;
        m = range;
        content.resize(n);
    }
    // created a function to generate random values for the code
    void initializeRandom() {
        // the for statement goes through each part in the code
        for (int i = 0; i < n; i++) {
            //created the statement to assign a random number to the range
            content[i] = rand() % m;
        }
    }

    // created a function called readGuess to implement the user to guess the number
    void readGuess() {
        // create a user input for guests to input their guests
        cout << "Enter guess: ";
          // the for statement goes through each part in the code
        for (int i = 0; i < n; i++) {
            // this statements stores the input value
            cin >> content[i];
        }
    }

    // this function will print the output of the code 
    void print() const {
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
        for (int i = 0; i < n; i++) {
            // the if statement compares the secret sequence and the guess
            if (digitAt(i) == guess.digitAt(i)) {
                usedSecret[i] = true;
                usedGuess[i] = true;
            }
        }

        // this statements initailize incorrect to be set to 0
        int incorrect = 0;
        // the for statement goes through each part in the code
        for (int i = 0; i < n; i++) {
            // if the guessed number matches the secret number, then the next number will be checked
            if (usedGuess[i]) continue;
                    // the for statement goes through each part in the code
            for (int j = 0; j < n; j++) {
                // if the guessed number matches the secret number, then the next number will be checked
                if (usedSecret[j]) continue;
                // created an if statement to identify if the guess number matches the secret number
                if (guess.digitAt(i) == digitAt(j)) {

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
    int checkCorrect(const code& guess) const {
        
        int correct = 0;
        for (int i=0; i < n; i++) {
            if (digitAt(i) == guess.digitAt(i)) {
                correct++;
            }
        }
        return correct;

    }


};

class response {
private:
    int numCorrect;
    int numIncorrect;

public:
    response(int c = 0, int i = 0) {
        numCorrect = c;
        numIncorrect = i;
    }

    int getCorrect() const {
        return numCorrect;
    }

    int getIncorrect() const {
        return numIncorrect;
    }

    void setCorrect(int c) {
        numCorrect = c;
    }

    void setIncorrect(int i) {
        numIncorrect = i;
    }
};

bool operator==(const response& r1, const response& r2) {
    bool sameCorrect = false;
    bool sameIncorrect = false;

    if (r1.getCorrect() == r2.getCorrect()) {
        sameCorrect = true;
    }

    if (r1.getIncorrect() == r2.getIncorrect()) {
        sameIncorrect = true;
    }

    if (sameCorrect && sameIncorrect) {
        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream& out, const response& r) {
    out << r.getCorrect();
    out << " correct location, ";
    out << r.getIncorrect();
    out << " incorrect location";
    return out;
}



void parta() {
    cout << "This is for the specific examples" << endl;
    int n = 5;
    int m = 7;

    code secretCode(n, m);
    secretCode.initializeRandom();

    cout << "Secret Code: ";
    secretCode.print();
    cout << endl;

    code guess1(n, m);
    guess1.setGuess({5, 0, 3, 2, 6});
    cout << "guess 1: ";
    guess1.print();
    cout << "Correct: " << secretCode.checkCorrect(guess1) << endl;
    cout << "Incorrect: " << secretCode.checkIncorrect(guess1) << endl << endl;

    code guess2(n, m);
    guess2.setGuess({2, 1, 2, 2, 2});
    cout << "Guess 2: ";
    guess2.print();
    cout << "Correct: " << secretCode.checkCorrect(guess2) << endl;
    cout << "Incorrect: " << secretCode.checkIncorrect(guess2) << endl << endl;    

    code guess3(n, m);
    guess2.setGuess({1, 3, 3, 4, 5});
    cout << "Guess 3: ";
    guess2.print();
    cout << "Correct: " << secretCode.checkCorrect(guess3) << endl;
    cout << "Incorrect: " << secretCode.checkIncorrect(guess3) << endl << endl;     
}



// define main function
int main() {
    // statement required to generate random values
    srand(time(0));

    // parta();
    // for part 2, of part a

    int n, m;

    // statement to ask user for the number of digits
    // 5 for the specific testing values
    cout << "How many digits: ";
    cin >> n;

    // statement to ask user for the digit range
    // 10 for the specific testing values
    cout << "What's the range?: ";
    cin >> m;

    // function to generate the secret code
    code secretCode(n, m);
    secretCode.initializeRandom();
    secretCode.print();

    // lets user know that secret code was generated
    cout << "Secret Code generated, you have 10 tries to guess" << endl;

    // initialize the maximum number of attempts
    int maxG = 10;
    // create a boolean to check if the player has won the game
    bool won = false;

    // starts loop, max of how many attempts
    for (int i = 1; i <= maxG; i++) {
        // displays current round number
        cout << "Round " << i << " of" << maxG << " " << "\n";
        
         // create a new code object to store user's input
        code guess(n, m);
        // calls the readGuess function to input the user's code
        guess.readGuess();

        // tracks how many digits are in the exact correct positios
        int correctLoc = secretCode.checkCorrect(guess);
        // tracks how many digits are the correct number but in the wrong position
        int incorrectLoc = secretCode.checkIncorrect(guess);

        // check if the number of correctly placed digits equals the total length
        // thus, the codebreaker correctly guessed the code
        if (correctLoc == n) {
            // prints that the codebreaker won
            cout << "\n codebreaker wins" << endl;
            cout << "You guessed the code in " << i << " tries." << endl;
            won = true;
            // updates the boolean that user won
            break;
        } else { // otherwise, tels user how many are in correct location or incorrect location
            cout << correctLoc << " correct location, " << incorrectLoc << " incorrect location." << endl << endl;
        }
    }

    // after loop, check if user failed
    if (!won) { // thus, codemaker wins
        cout << "codemaker wins" << endl;
        cout << "The correct code was: ";
        secretCode.print(); // show user what the code was
    }

    return 0;
}