// main.cpp
// Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Project 4 Part B - Sudoku Solver
//
// Reads Sudoku puzzles from a file, solves each one using
// recursive backtracking, prints the solution and the number of
// recursive calls, then prints the average across all boards.

#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

int main(int argc, char *argv[])
// Reads the filename from the command line, opens the file, and
// solves each puzzle in sequence.
{
   ifstream fin;

   if (argc < 2)
   {
      cerr << "Usage: ./sudoku <filename>" << endl;
      exit(1);
   }

   string fileName = argv[1];

   fin.open(fileName.c_str());

   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      board b1(SquareSize);

      int totalCalls = 0;
      int numBoards = 0;

      while (fin && fin.peek() != 'Z')
      {
         b1.initialize(fin);

         cout << "Initial board:" << endl;
         b1.print();

         int count = 0;

         if (b1.solve(count))
         {
            cout << endl << "Solved board:" << endl;
            b1.print();
            b1.isSolved();
         }
         else
         {
            cout << endl << "No solution found." << endl;
         }

         cout << "Recursive calls: " << count << endl;
         cout << "-----------------------------------" << endl;

         totalCalls += count;
         numBoards++;
      } // end while

      cout << endl;
      cout << "Total boards solved: " << numBoards << endl;
      cout << "Total recursive calls: " << totalCalls << endl;

      if (numBoards > 0)
      {
         cout << "Average recursive calls: "
              << (double)totalCalls / numBoards << endl;
      }
   }
   catch (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
} // end main
