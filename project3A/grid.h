// grid.h
// Maddox Grillo-Smith, Ryan Kim, Vishnu Kumar, Preeth Somanchi
// Project 3B

// Header file for the grid class. Stores a 2D character grid
// read from a file using the d_matrix class.

#ifndef GRID_H
#define GRID_H

#include <string>
#include "d_matrix.h"

using namespace std;

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

#endif