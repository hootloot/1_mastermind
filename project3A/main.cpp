// File: main.cpp
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project 3A

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

// Stores a list of words from a file and provides sorting
// and searching functionality to look up words efficiently.
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

// Default constructor, nothing to initialize since vector is empty
dictionary::dictionary() {}

// Reads all words from the given file and stores them in the vector.
// Each word should be on its own line or separated by whitespace.
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

// Returns how many words are in the dictionary
int dictionary::size() const
{
    return words.size();
}

// Overloaded output operator to print all words in the dictionary,
// one per line. Useful for debugging.
ostream &operator<<(ostream &os, const dictionary &d)
{
    for (int i = 0; i < (int)d.words.size(); i++)
        os << d.words[i] << endl;
    return os;
}

// Sorts the word list alphabetically using selection sort.
// For each position i, finds the smallest word in the rest of the
// list and swaps it into place. O(n^2) but simple to implement.
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

// Searches for a word in the sorted dictionary using binary search.
// Repeatedly splits the search range in half until the word is found
// or the range is empty. Returns the index if found, -1 if not.
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

// Stores the letter grid from a file using the provided matrix class.
// Gives access to individual characters and the grid dimensions.
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

// Default constructor, grid starts empty
grid::grid() : rows(0), cols(0) {}

// Reads the grid from a file. First line has the row and column count,
// followed by rows of space-separated characters.
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

// Goes through every cell in the grid and tries all 8 directions.
// For each direction, builds up a string one character at a time.
// Once the string is 5+ characters, it checks the dictionary using
// binary search. If found and not already printed, it outputs the word.
// Wrapping is handled with modulo so going off one edge comes back
// on the opposite side. Uses a set to avoid printing duplicates.
void findMatches(const dictionary &dict, const grid &g, const string &outputFile)
{
    int n = g.getRows();
    int m = g.getCols();

    // Direction offsets for: N, NE, E, SE, S, SW, W, NW
    int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

    ofstream fout(outputFile.c_str());
    set<string> found; // keeps track of words already printed

    // Try every starting cell
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Try all 8 directions from this cell
            for (int d = 0; d < 8; d++)
            {
                string word = "";
                int r = i, c = j;

                // Walk up to max(n,m) steps — after that we'd wrap
                // back to the start and repeat characters
                int maxSteps = (n > m) ? n : m;

                for (int step = 0; step < maxSteps; step++)
                {
                    word += g.getChar(r, c);

                    // Only look up words that are at least 5 chars long
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

                    // Move to next cell in this direction, wrapping around
                    // the +n and +m prevent negative values before the mod
                    r = (r + dr[d] + n) % n;
                    c = (c + dc[d] + m) % m;
                }
            }
        }
    }

    fout.close();
    cout << endl << "Total words found: " << found.size() << endl;
}

// Main driver function. Asks the user for the grid filename,
// reads in both the dictionary and the grid, sorts the dictionary,
// then calls findMatches to search for all valid words.
void search()
{
    string gridFile;
    cout << "Enter grid filename: ";
    cin >> gridFile;

    // Read in all the words from the dictionary file
    dictionary dict;
    cout << "Reading dictionary..." << endl;
    dict.readWords("Dictionary");
    cout << "Dictionary loaded: " << dict.size() << " words" << endl;

    // Read in the letter grid
    grid g;
    g.readGrid(gridFile);
    cout << "Grid loaded: " << g.getRows() << " x " << g.getCols() << endl;

    // Sort the dictionary so we can use binary search later
    cout << "Sorting dictionary (selection sort)..." << endl;
    dict.selectionSort();
    cout << "Sort complete." << endl;

    // Search the grid and write results to an output file
    string outputFile = gridFile.substr(0, gridFile.find('.')) + "_results.txt";
    cout << "Searching for matches..." << endl << endl;
    findMatches(dict, g, outputFile);
    cout << "Results written to " << outputFile << endl;
}

// Main just calls search() inside a try-catch to handle
// any file errors or other exceptions from d_except.h
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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

// Stores a list of words from a file and provides sorting
// and searching functionality to look up words efficiently.
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

// Default constructor, nothing to initialize since vector is empty
dictionary::dictionary() {}

// Reads all words from the given file and stores them in the vector.
// Each word should be on its own line or separated by whitespace.
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

// Returns how many words are in the dictionary
int dictionary::size() const
{
    return words.size();
}

// Overloaded output operator to print all words in the dictionary,
// one per line. Useful for debugging.
ostream &operator<<(ostream &os, const dictionary &d)
{
    for (int i = 0; i < (int)d.words.size(); i++)
        os << d.words[i] << endl;
    return os;
}

// Sorts the word list alphabetically using selection sort.
// For each position i, finds the smallest word in the rest of the
// list and swaps it into place. O(n^2) but simple to implement.
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

// Searches for a word in the sorted dictionary using binary search.
// Repeatedly splits the search range in half until the word is found
// or the range is empty. Returns the index if found, -1 if not.
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

// Stores the letter grid from a file using the provided matrix class.
// Gives access to individual characters and the grid dimensions.
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

// Default constructor, grid starts empty
grid::grid() : rows(0), cols(0) {}

// Reads the grid from a file. First line has the row and column count,
// followed by rows of space-separated characters.
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

// Goes through every cell in the grid and tries all 8 directions.
// For each direction, builds up a string one character at a time.
// Once the string is 5+ characters, it checks the dictionary using
// binary search. If found and not already printed, it outputs the word.
// Wrapping is handled with modulo so going off one edge comes back
// on the opposite side. Uses a set to avoid printing duplicates.
void findMatches(const dictionary &dict, const grid &g, const string &outputFile)
{
    int n = g.getRows();
    int m = g.getCols();

    // Direction offsets for: N, NE, E, SE, S, SW, W, NW
    int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

    ofstream fout(outputFile.c_str());
    set<string> found; // keeps track of words already printed

    // Try every starting cell
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Try all 8 directions from this cell
            for (int d = 0; d < 8; d++)
            {
                string word = "";
                int r = i, c = j;

                // Walk up to max(n,m) steps — after that we'd wrap
                // back to the start and repeat characters
                int maxSteps = (n > m) ? n : m;

                for (int step = 0; step < maxSteps; step++)
                {
                    word += g.getChar(r, c);

                    // Only look up words that are at least 5 chars long
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

                    // Move to next cell in this direction, wrapping around
                    // the +n and +m prevent negative values before the mod
                    r = (r + dr[d] + n) % n;
                    c = (c + dc[d] + m) % m;
                }
            }
        }
    }

    fout.close();
    cout << endl << "Total words found: " << found.size() << endl;
}

// Main driver function. Asks the user for the grid filename,
// reads in both the dictionary and the grid, sorts the dictionary,
// then calls findMatches to search for all valid words.
void search()
{
    string gridFile;
    cout << "Enter grid filename: ";
    cin >> gridFile;

    // Read in all the words from the dictionary file
    dictionary dict;
    dict.readWords("Dictionary");
    cout << "Dictionary loaded: " << dict.size() << " words" << endl;

    // Read in the letter grid
    grid g;
    g.readGrid(gridFile);
    cout << "Grid loaded: " << g.getRows() << " x " << g.getCols() << endl;

    // Sort the dictionary so we can use binary search later
    dict.selectionSort();
    cout << "Sort complete." << endl;

    // Search the grid and write results to an output file
    string outputFile = gridFile.substr(0, gridFile.find('.')) + "_results.txt";
    findMatches(dict, g, outputFile);
    cout << "Results written to " << outputFile << endl;
}

// Main just calls search() inside a try-catch to handle
// any file errors or other exceptions from d_except.h
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