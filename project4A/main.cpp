// Project 4a - Sudoku Main
// Ryan
// EECE 2560
//
// Reads Sudoku puzzles from a file, prints each board with its
// conflict info, and checks whether each board is solved.

#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

int main(int argc, char *argv[])
{
   ifstream fin;

   // Get the filename from the command line, or default to sudoku.txt

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

      while (fin && fin.peek() != 'Z')
      {
         b1.initialize(fin);
         b1.print();
         b1.printConflicts();
         b1.isSolved();
         cout << "-----------------------------------" << endl;
      }
   }
   catch (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}