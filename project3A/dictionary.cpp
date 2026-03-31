// dictionary.cpp
// Maddox Grillo-Smith, Ryan Kim, Vishnu Kumar, Preeth Somanchi
// Project 3B

// Implementation of the dictionary class. Reads words from a file
// and provides three sorting algorithms and binary search.

#include <fstream>
#include "dictionary.h"
#include "heap.h"
#include "d_except.h"

dictionary::dictionary()
// Default constructor. The words vector starts empty.
{
}

void dictionary::readWords(const string &filename)
// Opens the given file and reads every word into the vector.
// Throws a fileOpenError if the file can't be opened.
// The input is the file containing one word per line
{
   ifstream fin(filename.c_str());

   if (!fin)
   {
      throw fileOpenError(filename);
   }

   string word;

   while (fin >> word)
   {
      words.push_back(word);
   }

   fin.close();
}

int dictionary::size() const
// Returns the number of words currently stored.
{
   return words.size();
}

ostream &operator<<(ostream &os, const dictionary &d)
// Prints every word in the dictionary, one per line.
// input is an output stream os and a dictionary object d
// the output stream is in a valid state
{
   for (int i = 0; i < (int)d.words.size(); i++)
   {
      os << d.words[i] << endl;
   }

   return os;
}

void dictionary::selectionSort()
// Sorts the words using selection sort. Scans for the minimum
// element in the unsorted portion and swaps it into place.

{
   int n = words.size();

   for (int i = 0; i < n - 1; i++)
   {
      int minIdx = i;

      for (int j = i + 1; j < n; j++)
      {
         if (words[j] < words[minIdx])
         {
            minIdx = j;
         }
      } // end inner for

      if (minIdx != i)
      {
         swap(words[i], words[minIdx]);
      }
   } // end outer for 
}

int dictionary::partition(int low, int high)
// Partitions the subarray words[low..high] around the last
// element as the pivot. Returns the final index of the pivot.
// int low and int high are indices into the words vector
// defining the range to partition
{
   string pivot = words[high];
   int i = low - 1;

   for (int j = low; j < high; j++)
   {
      if (words[j] <= pivot)
      {
         i++;
         swap(words[i], words[j]);
      }
   } // end for 

   swap(words[i + 1], words[high]);
   return i + 1;
}

void dictionary::quickSortHelper(int low, int high)
// Recursive quicksort on words[low..high]. Partitions the
// range and then sorts each half.
// int low and int high are indices into the words vector
// defining the range to partition
{
   if (low < high)
   {
      int pi = partition(low, high);
      quickSortHelper(low, pi - 1);
      quickSortHelper(pi + 1, high);
   }
}

void dictionary::quickSort()
// Public quicksort function. Kicks off the recursive helper
// on the full range of the words vector.
{
   if (!words.empty())
   {
      quickSortHelper(0, (int)words.size() - 1);
   }
}

void dictionary::heapSort()
// Sorts the words using heapsort. Creates a heap object,
// copies the words in, sorts them, and copies the result back.
{
   heap<string> h;
   h.initializeMaxHeap(words);
   words = h.heapsort();
}

int dictionary::binarySearch(const string &word) const
// Looks up a word in the sorted vector using binary search.
// we input the string to search for
// Returns the index if found, -1 otherwise.
// Assumes the vector has already been sorted.
{
   int low = 0;
   int high = (int)words.size() - 1;

   while (low <= high)
   {
      int mid = (low + high) / 2;

      if (words[mid] == word)
      {
         return mid;
      }
      else if (words[mid] < word)
      {
         low = mid + 1;
      }
      else
      {
         high = mid - 1;
      }
   } 

   return -1;
}