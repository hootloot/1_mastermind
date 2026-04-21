// board.h
// Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Project 4 Part B - Sudoku Solver
//
// Contains the board class which stores a Sudoku puzzle and
// provides functions to read, print, check conflicts, and solve
// the board using recursive backtracking.

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <fstream>

using namespace std;

typedef int ValueType;
const int Blank = -1;

const int SquareSize = 3;
const int BoardSize = SquareSize * SquareSize;
const int MinValue = 1;
const int MaxValue = 9;

int squareNumber(int i, int j)
// Returns which 3x3 square cell (i,j) belongs to, numbered
// 1-9 from left to right, top to bottom.
{
   return SquareSize * ((i - 1) / SquareSize)
          + (j - 1) / SquareSize + 1;
}

class board
{
   public:
      board(int);
      void clear();
      void initialize(ifstream &fin);
      void print();
      bool isBlank(int, int);
      ValueType getCell(int, int);
      void setCell(int i, int j, int val);
      void clearCell(int i, int j);
      void printConflicts();
      bool isSolved();
      bool isLegal(int i, int j, int val);
      bool findNextBlank(int &row, int &col);
      bool solve(int &count);

   private:
      matrix<ValueType> value;    // the 9x9 grid of cell values

      // conflict tracking: true means that digit is already used
      matrix<bool> rowConf;       // rowConf[i][v] = v in row i
      matrix<bool> colConf;       // colConf[j][v] = v in col j
      matrix<bool> sqConf;        // sqConf[s][v]  = v in square s
};

board::board(int sqSize)
   : value(BoardSize + 1, BoardSize + 1),
     rowConf(BoardSize + 1, MaxValue + 1, false),
     colConf(BoardSize + 1, MaxValue + 1, false),
     sqConf(BoardSize + 1, MaxValue + 1, false)
// Constructor. Sets up all matrices indexed from 1 to BoardSize.
{
   clear();
}

void board::clear()
// Resets the board to blank and clears all conflict flags.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         value[i][j] = Blank;
      }
   }

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int v = MinValue; v <= MaxValue; v++)
      {
         rowConf[i][v] = false;
         colConf[i][v] = false;
         sqConf[i][v] = false;
      }
   }
}

void board::initialize(ifstream &fin)
// Reads a Sudoku board from the input stream. Each puzzle is 81
// characters on one line, where '.' means blank and digits 1-9
// are given clues. Updates conflict matrices as cells are placed.
{
   char ch;

   clear();

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         fin >> ch;

         if (ch != '.')
            setCell(i, j, ch - '0');
      }
   }
}

void board::setCell(int i, int j, int val)
// Places val in cell (i,j) and sets the conflict flags for
// the corresponding row, column, and square.
// Throws rangeError if i, j, or val is out of bounds.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   if (val < MinValue || val > MaxValue)
      throw rangeError("bad value in setCell");

   value[i][j] = val;
   rowConf[i][val] = true;
   colConf[j][val] = true;
   sqConf[squareNumber(i, j)][val] = true;
}

void board::clearCell(int i, int j)
// Removes the digit from cell (i,j) and unsets its conflict
// flags. Does nothing if the cell is already blank.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in clearCell");

   if (isBlank(i, j))
      return;

   int val = value[i][j];
   value[i][j] = Blank;
   rowConf[i][val] = false;
   colConf[j][val] = false;
   sqConf[squareNumber(i, j)][val] = false;
}

ValueType board::getCell(int i, int j)
// Returns the value in cell (i,j).
// Throws rangeError if out of bounds.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell (i,j) is blank, false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in isBlank");

   return (getCell(i, j) == Blank);
}

void board::print()
// Prints the board with dividers between the 3x3 squares.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i - 1) % SquareSize == 0)
      {
         cout << " -";

         for (int j = 1; j <= BoardSize; j++)
            cout << "---";

         cout << "-";
         cout << endl;
      }

      for (int j = 1; j <= BoardSize; j++)
      {
         if ((j - 1) % SquareSize == 0)
            cout << "|";

         if (!isBlank(i, j))
            cout << " " << getCell(i, j) << " ";
         else
            cout << "   ";
      }

      cout << "|";
      cout << endl;
   } // end row loop

   cout << " -";

   for (int j = 1; j <= BoardSize; j++)
      cout << "---";

   cout << "-";
   cout << endl;
}

void board::printConflicts()
// Prints which digits are present in each row, column, and
// square. Useful for debugging.
{
   cout << endl;
   cout << "Row conflicts:" << endl;

   for (int i = 1; i <= BoardSize; i++)
   {
      cout << "  Row " << i << ": ";

      for (int v = MinValue; v <= MaxValue; v++)
      {
         if (rowConf[i][v])
            cout << v << " ";
      }

      cout << endl;
   }

   cout << endl;
   cout << "Column conflicts:" << endl;

   for (int j = 1; j <= BoardSize; j++)
   {
      cout << "  Col " << j << ": ";

      for (int v = MinValue; v <= MaxValue; v++)
      {
         if (colConf[j][v])
            cout << v << " ";
      }

      cout << endl;
   }

   cout << endl;
   cout << "Square conflicts:" << endl;

   for (int s = 1; s <= BoardSize; s++)
   {
      cout << "  Sq  " << s << ": ";

      for (int v = MinValue; v <= MaxValue; v++)
      {
         if (sqConf[s][v])
            cout << v << " ";
      }

      cout << endl;
   }

   cout << endl;
} // end printConflicts

bool board::isSolved()
// Checks if every row, column, and square has all digits 1-9.
// Prints whether the board is solved and returns true/false.
{
   // make sure there are no blank cells left

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         if (isBlank(i, j))
         {
            cout << "Board is NOT solved (has blank cells)."
                 << endl;
            return false;
         }
      }
   }

   // check that each row has all digits

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int v = MinValue; v <= MaxValue; v++)
      {
         if (!rowConf[i][v])
         {
            cout << "Board is NOT solved (row " << i
                 << " missing " << v << ")." << endl;
            return false;
         }
      }
   }

   // check columns

   for (int j = 1; j <= BoardSize; j++)
   {
      for (int v = MinValue; v <= MaxValue; v++)
      {
         if (!colConf[j][v])
         {
            cout << "Board is NOT solved (col " << j
                 << " missing " << v << ")." << endl;
            return false;
         }
      }
   }

   // check squares

   for (int s = 1; s <= BoardSize; s++)
   {
      for (int v = MinValue; v <= MaxValue; v++)
      {
         if (!sqConf[s][v])
         {
            cout << "Board is NOT solved (square " << s
                 << " missing " << v << ")." << endl;
            return false;
         }
      }
   }

   cout << "Board is solved!" << endl;
   return true;
} // end isSolved

bool board::isLegal(int i, int j, int val)
// Checks whether placing val at cell (i,j) would cause a
// conflict. Returns true if val is not already in the same row,
// column, or 3x3 square. Assumes (i,j) is a valid blank cell.
{
   if (rowConf[i][val])
      return false;

   if (colConf[j][val])
      return false;

   if (sqConf[squareNumber(i, j)][val])
      return false;

   return true;
}

bool board::findNextBlank(int &row, int &col)
// Finds the blank cell with the fewest legal candidate values.
// This is the most-constrained-variable heuristic, which helps
// cut down on backtracking. Sets row and col to the chosen
// cell. Returns false if no blank cells remain.
{
   int minOptions = MaxValue + 1;
   bool found = false;

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         if (!isBlank(i, j))
            continue;

         // count how many digits can legally go here

         int numLegal = 0;

         for (int v = MinValue; v <= MaxValue; v++)
         {
            if (isLegal(i, j, v))
               numLegal++;
         }

         if (numLegal < minOptions)
         {
            minOptions = numLegal;
            row = i;
            col = j;
            found = true;

            // 0 or 1 option is the best we can get

            if (minOptions <= 1)
               return true;
         }
      } // end col loop
   } // end row loop

   return found;
} // end findNextBlank

bool board::solve(int &count)
// Recursively solves the board using backtracking. Picks the
// most constrained blank cell, tries each legal digit 1-9, and
// recurses. If no digit works, clears the cell and backtracks.
// Returns true when a solution is found (no exit() used).
// count is incremented each recursive call for tracking.
{
   count++;

   int row, col;

   // base case: no blanks left means the puzzle is complete

   if (!findNextBlank(row, col))
      return true;

   // try placing each digit in this cell

   for (int val = MinValue; val <= MaxValue; val++)
   {
      if (isLegal(row, col, val))
      {
         setCell(row, col, val);

         if (solve(count))
            return true;

         // didn't work, undo and try the next digit

         clearCell(row, col);
      }
   }

   // none of the digits worked, backtrack

   return false;
} // end solve

#endif // BOARD_H
