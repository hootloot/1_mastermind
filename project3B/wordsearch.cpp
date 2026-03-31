// wordsearch.cpp
// Maddox Grillo-Smith, Ryan Kim, Vishnu Kumar, Preeth Somanchi
// Project 3B

// Main driver for the word search program. 
// Reads a grid file,
// sorts the dictionary with a user-selected algorithm
// searches for all valid 5+ letter words in all 8 directions


#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "dictionary.h"
#include "grid.h"
#include "d_except.h"

using namespace std;

int gcdInt(int a, int b)
// Computes the GCD of a and b using Euclid's algorithm.
// Used to figure out the diagonal wrap cycle length.
// Inputs: two pos int a and b, if both are positive
{
   while (b != 0)
   {
      int t = a % b;
      a = b;
      b = t;
   }

   return a;
}

int stepsInDirection(int rows, int cols, int dr, int dc)
// Returns the max number of unique cells you'd visit walking
// in direction (dr, dc) with wrapping before looping back.
// Horizontal = cols, vertical = rows, diagonal = lcm(rows, cols).
// inputs: rows and cols (grid dimensions)
// and dr and dc are driection vector components
{
   if (dr == 0)
   {
      return cols;
   }

   if (dc == 0)
   {
      return rows;
   }

   // diagonal case: lcm(rows, cols) = rows * cols / gcd
   return (rows * cols) / gcdInt(rows, cols);
}

void findMatches(const dictionary &dict, const grid &g,
                 const string &outputFile)
// Searches every starting cell in every direction for words.
// Builds up a string character by character, and once it's at
// least 5 characters long, looks it up in the dictionary with
// binary search. Results are written to outputFile.
// Uses modulo arithmetic so the grid wraps around.
{
   int n = g.getRows();
   int m = g.getCols();

   // direction vectors: N, NE, E, SE, S, SW, W, NW
   int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
   int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

   ofstream fout(outputFile.c_str());

   if (!fout)
   {
      throw fileOpenError(outputFile);
   }

   int totalMatches = 0;

   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         for (int d = 0; d < 8; d++)
         {
            string word = "";
            int r = i;
            int c = j;
            int maxSteps = stepsInDirection(n, m, dr[d], dc[d]);

            for (int step = 0; step < maxSteps; step++)
            {
               word += g.getChar(r, c);

               // only check words that are 5+ characters
               if ((int)word.length() >= 5)
               {
                  int idx = dict.binarySearch(word);

                  if (idx != -1)
                  {
                     fout << word << " (" << i << ","
                          << j << ") " << idx << endl;
                     totalMatches++;
                  }
               }

               // wrap around using modulo
               r = (r + dr[d] + n) % n;
               c = (c + dc[d] + m) % m;
            } // end step loop
         } // end direction loop
      } // end col loop
   } // end row loop

   fout.close();
   cout << "Total matches found: " << totalMatches << endl;
}

void search(int sortChoice)
// Reads the grid filename from the user, loads the dictionary
// and grid, sorts using the chosen algorithm and runs the word search.
// input: is the user's choice int
{
   string gridFile;
   cout << "Enter grid filename: ";
   cin >> gridFile;

   // load dictionary
   dictionary dict;
   dict.readWords("Dictionary");
   cout << "Dictionary loaded: " << dict.size()
        << " words" << endl;

   // load grid
   grid g;
   g.readGrid(gridFile);
   cout << "Grid loaded: " << g.getRows() << " x "
        << g.getCols() << endl;

   // time the selected sorting algorithm
   auto start = chrono::steady_clock::now();

   switch (sortChoice)
   {
      case 1:
         cout << "Sorting with selection sort" << endl;
         dict.selectionSort();
         break;
      case 2:
         cout << "Sorting with quicksort" << endl;
         dict.quickSort();
         break;
      case 3:
         cout << "Sorting with heapsort" << endl;
         dict.heapSort();
         break;
      default:
         cout << "Invalid choice, using quicksort" << endl;
         dict.quickSort();
         break;
   } // end switch

   auto end = chrono::steady_clock::now();
   double elapsed = chrono::duration<double>(end - start).count();

   cout << "Sort complete. Time: " << elapsed
        << " seconds" << endl;

   // build output filename from grid filename
   string outputFile = gridFile.substr(0, gridFile.find('.'))
                       + "_results.txt";

   findMatches(dict, g, outputFile);
}

int main()
// Entry point. Asks which sort to use and runs the search.
// Catches any file errors from d_except.h.
{
   try
   {
      int choice;
      cout << "Select sorting algorithm:" << endl;
      cout << "  1) Selection sort" << endl;
      cout << "  2) Quicksort" << endl;
      cout << "  3) Heapsort" << endl;
      cout << "Choice: ";
      cin >> choice;

      search(choice);
   }
   catch (baseException &ex)
   {
      cerr << "Error: " << ex.what() << endl;
      return 1;
   }

   return 0;
}