#include <vector>
#include<cstdlib>
#include <ctime>
#include<iostream>
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
