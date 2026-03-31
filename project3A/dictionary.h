// dictionary.h
// Maddox Grillo-Smith, Ryan Kim, Vishnu Kumar, Preeth Somanchi
// Project 3B

// Header file for the dictionary class. Holds a list of words
// and supports sorting (selection sort, quicksort, heapsort)
// and binary search lookup.

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class dictionary
{
   public:
      dictionary();
      void readWords(const string &filename);
      void selectionSort();
      void quickSort();
      void heapSort();
      int binarySearch(const string &word) const;
      int size() const;
      friend ostream &operator<<(ostream &os, const dictionary &d);

   private:
      vector<string> words;
      void quickSortHelper(int low, int high);
      int partition(int low, int high);
};

#endif