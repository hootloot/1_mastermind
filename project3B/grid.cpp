// grid.cpp
// Maddox Grillo-Smith, Ryan Kim, Vishnu Kumar, Preeth Somanchi
// Project 3B

// Implementation of the grid class. Reads a character grid
// from a file where the first line has the dimensions.

#include <fstream>
#include "grid.h"
#include "d_except.h"

grid::grid() : rows(0), cols(0)
// Default constructor. Grid starts with zero size.
{
}

void grid::readGrid(const string &filename)
// Reads the grid from the given file. The first line should
// contain the number of rows and columns. The rest of the file
// has space-separated characters filling the grid.
// Throws fileOpenError if the file can't be opened.
{
   ifstream fin(filename.c_str());

   if (!fin)
   {
      throw fileOpenError(filename);
   }

   fin >> rows >> cols;
   mat.resize(rows, cols);

   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < cols; j++)
      {
         fin >> mat[i][j];
      }
   } // end for 

   fin.close();
}

int grid::getRows() const
// Returns the number of rows in the grid.
{
   return rows;
}

int grid::getCols() const
// Returns the number of columns in the grid.
{
   return cols;
}

char grid::getChar(int i, int j) const
// Returns the character at row i, column j.
// inputs: i is the row index, j is the column index
// i is in [0, rows) and j is in [0, cols)
{
   return mat[i][j];
}