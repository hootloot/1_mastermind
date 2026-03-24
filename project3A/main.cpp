#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

// ===================== dictionary class =====================
class dictionary
{
public:
    dictionary();
    void readWords(const string &filename);
    void selectionSort();
    int binarySearch(const string &word) const;
    int size() const;
    friend ostream &operator<<(ostream &os, const dictionary &d);

private:
    vector<string> words;
};

dictionary::dictionary() {}

void dictionary::readWords(const string &filename)
{
    ifstream fin(filename.c_str());
    if (!fin)
        throw fileOpenError(filename);
    string word;
    while (fin >> word)
        words.push_back(word);
    fin.close();
}

int dictionary::size() const
{
    return words.size();
}

ostream &operator<<(ostream &os, const dictionary &d)
{
    for (int i = 0; i < (int)d.words.size(); i++)
        os << d.words[i] << endl;
    return os;
}

// Selection sort: O(n^2) — required by spec for Part A
void dictionary::selectionSort()
{
    int n = words.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (words[j] < words[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(words[i], words[minIdx]);
    }
}

// Binary search: O(log n) — returns index if found, -1 otherwise
int dictionary::binarySearch(const string &word) const
{
    int low = 0, high = (int)words.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (words[mid] == word)
            return mid;
        else if (words[mid] < word)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// ===================== grid class =====================
class grid
{
public:
    grid();
    void readGrid(const string &filename);
    int getRows() const;
    int getCols() const;
    char getChar(int i, int j) const;

private:
    matrix<char> mat;
    int rows, cols;
};

grid::grid() : rows(0), cols(0) {}

void grid::readGrid(const string &filename)
{
    ifstream fin(filename.c_str());
    if (!fin)
        throw fileOpenError(filename);
    fin >> rows >> cols;
    mat.resize(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> mat[i][j];
    fin.close();
}

int grid::getRows() const { return rows; }
int grid::getCols() const { return cols; }
char grid::getChar(int i, int j) const { return mat[i][j]; }

// ===================== findMatches =====================
// Scans every cell in every direction, builds candidate strings
// of length 5..n, and looks each up via binary search.
// Wrapping handled with modular arithmetic.
// Uses a set to avoid printing duplicate words.
void findMatches(const dictionary &dict, const grid &g, const string &outputFile)
{
    int n = g.getRows();
    int m = g.getCols();

    // 8 directions: N, NE, E, SE, S, SW, W, NW
    int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

    ofstream fout(outputFile.c_str());
    set<string> found; // track unique words

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Try all 8 directions from cell (i, j)
            for (int d = 0; d < 8; d++)
            {
                string word = "";
                int r = i, c = j;

                // Walk up to max(n, m) steps before wrap repeats
                int maxSteps = (n > m) ? n : m;

                for (int step = 0; step < maxSteps; step++)
                {
                    word += g.getChar(r, c);

                    // Only search words of length >= 5
                    if ((int)word.length() >= 5)
                    {
                        int idx = dict.binarySearch(word);
                        if (idx != -1 && found.find(word) == found.end())
                        {
                            found.insert(word);
                            cout << "found: " << word << endl;
                            fout << "found: " << word << endl;
                        }
                    }

                    // Advance with wrapping
                    r = (r + dr[d] + n) % n;
                    c = (c + dc[d] + m) % m;
                }
            }
        }
    }

    fout.close();
    cout << endl << "Total words found: " << found.size() << endl;
}

// ===================== search (main driver) =====================
void search()
{
    string gridFile;
    cout << "Enter grid filename: ";
    cin >> gridFile;

    // 1. Read dictionary
    dictionary dict;
    cout << "Reading dictionary..." << endl;
    dict.readWords("Dictionary");
    cout << "Dictionary loaded: " << dict.size() << " words" << endl;

    // 2. Read grid
    grid g;
    g.readGrid(gridFile);
    cout << "Grid loaded: " << g.getRows() << " x " << g.getCols() << endl;

    // 3. Sort dictionary
    cout << "Sorting dictionary (selection sort)..." << endl;
    dict.selectionSort();
    cout << "Sort complete." << endl;

    // 4. Find and print matches
    string outputFile = gridFile.substr(0, gridFile.find('.')) + "_results.txt";
    cout << "Searching for matches..." << endl << endl;
    findMatches(dict, g, outputFile);
    cout << "Results written to " << outputFile << endl;
}

int main()
{
    try
    {
        search();
    }
    catch (baseException &ex)
    {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
    return 0;
}