#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class code {
private:
    vector<int> content;
    int n;
    int m;

public:
    code(int length, int range) {
        n = length;
        m = range;
        content.resize(n);
    }

    void initializeRandom() {
        for (int i = 0; i < n; i++) {
            content[i] = rand() % m;
        }
    }

    void readGuess() {
        cout << "Enter guess: ";
        for (int i = 0; i < n; i++) {
            cin >> content[i];
        }
    }

    void print() const {
        for (int i = 0; i < n; i++) {
            cout << content[i] << (i < n - 1 ? ", " : "");
        }
        cout << endl;
    }

    int length() const { return n; }
    int digitAt(int i) const { return content[i]; }

   
    int checkIncorrect(const code& guess) const {
        vector<bool> usedSecret(n, false);
        vector<bool> usedGuess(n, false);

        for (int i = 0; i < n; i++) {
            if (digitAt(i) == guess.digitAt(i)) {
                usedSecret[i] = true;
                usedGuess[i] = true;
            }
        }

      
        int incorrect = 0;
        for (int i = 0; i < n; i++) {
            if (usedGuess[i]) continue;

            for (int j = 0; j < n; j++) {
                if (usedSecret[j]) continue;

                if (guess.digitAt(i) == digitAt(j)) {
                    incorrect++;
                    usedSecret[j] = true; 
                    break;                
                }
            }
        }

        return incorrect;
    }
    int checkCorrect(const code& guess) const {
        int i;
        int k;
        int correct;
        for (i=0; i < n; i++) {
            for (k=0; k < n; k++) {
                if (digitAt(i) == guess.digitAt(k)) {
                    correct++;
                    break;
                }
            }
        }
        return correct;

    }


};

int main() {
    srand(time(0));
    int n, m;

    cout << "How many digits: ";
    cin >> n;
    cout << endl;

    cout << "What's the range?: ";
    cin >> m;
    cout << endl;

    code secretCode(n, m);
    secretCode.initializeRandom();
    secretCode.print();

    cout << "Secret Code generated" << endl;

    code guess(n, m);
    guess.readGuess();
    guess.print();

   
    return 0;
}
