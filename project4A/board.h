// File: board.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Sudoku part A

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  // The number of cells in a small square
                           // (usually 3). The board has
                           // SquareSize^2 rows and SquareSize^2
                           // columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom). 
{
   // (i-1)/SquareSize and (j-1)/SquareSize give the x-y coordinates
   // of the square that (i,j) is in.

   return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

class board
// Stores the entire Sudoku board
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

   private:

      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

      matrix<ValueType> value;
      
      // rowConf[i][v] = true if digit v is placed in row i
      // colConf[j][v] = true if digit v is placed in col j
      // sqConf[s][v]  = true if digit v is placed in square s

      matrix<bool> rowConf;
      matrix<bool> colConf;
      matrix<bool> sqConf;
};

board::board(int sqSize)
   : value(BoardSize + 1, BoardSize + 1),
     rowConf(BoardSize + 1, MaxValue + 1, false),
     colConf(BoardSize + 1, MaxValue + 1, false),
     sqConf(BoardSize + 1, MaxValue + 1, false)
// Board constructor. Initializes the value matrix and all three
// conflict matrices.
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

   // Reset all conflict flags to false

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
// Read a Sudoku board from the input file. Each board is one line
// of 81 characters where '.' is blank and digits are filled in.
// Updates conflicts as each cell is set.
{
   char ch;

   clear();

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         fin >> ch;

         // If the char is a digit, place it on the board

         if (ch != '.')
            setCell(i, j, ch - '0');
      }
   }
}

void board::setCell(int i, int j, int val)
// Places val in cell (i,j) and marks the corresponding row, column,
// and square conflict flags. Throws rangeError if out of bounds.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   if (val < MinValue || val > MaxValue)
      throw rangeError("bad value in setCell");

   value[i][j] = val;

   // Flag this digit as present in its row, col, and square

   rowConf[i][val] = true;
   colConf[j][val] = true;
   sqConf[squareNumber(i, j)][val] = true;
}

void board::clearCell(int i, int j)
// Clears cell (i,j) and removes its conflict flags.
// Does nothing if the cell is already blank.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in clearCell");

   if (isBlank(i, j))
      return;

   int val = value[i][j];
   value[i][j] = Blank;

   // Unflag this digit from its row, col, and square

   rowConf[i][val] = false;
   colConf[j][val] = false;
   sqConf[squareNumber(i, j)][val] = false;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell. Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in isBlank");

   return (getCell(i, j) == Blank);
}

void board::print()
// Prints the current board.
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
   }

   cout << " -";

   for (int j = 1; j <= BoardSize; j++)
      cout << "---";

   cout << "-";
   cout << endl;
}

void board::printConflicts()
// Prints which digits have been placed in each row, column, and
// square. Helpful for verifying constraints are tracked right.
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
}

bool board::isSolved()
// Checks if the board is completely and correctly filled in.
// Every row, column, and square must have digits 1-9 exactly once.
// Prints the result and returns true/false.
{
   // Make sure no cell is blank

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         if (isBlank(i, j))
         {
            cout << "Board is NOT solved (has blank cells)." << endl;
            return false;
         }
      }
   }

   // Check rows

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

   // Check columns

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

   // Check squares

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
}

#endif // BOARD_H