// heap.h
// Maddox Grillo-Smith, Ryan Kim, Vishnu Kumar, Preeth Somanchi
// Project 3B

// Template heap class that uses a vector to store items in a
// max-heap structure and provides a heapsort function.
// Defaults to string if no type is given.

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>

using namespace std;

template <typename T = string>
class heap
{
   public:
      heap();

      int parent(int i) const; // parent index of node i
      int left(int i) const; // left child index
      int right(int i) const; // right child index
      T getItem(int n) const; // returns nth item

      void initializeMaxHeap(const vector<T> &items);
      void maxHeapify(int i, int heapSize);
      void buildMaxHeap();

      vector<T> heapsort();

   private:
      vector<T> data;
};

template <typename T>
heap<T>::heap()
// Default constructor
{
}

template <typename T>
int heap<T>::parent(int i) const
// Returns the index of the parent of node i
// int i is a index in the heap
{
   return (i - 1) / 2;
}

template <typename T>
int heap<T>::left(int i) const
// Returns the index of the left child of node i
// i is a index in the heap
{
   return 2 * i + 1;
}

template <typename T>
int heap<T>::right(int i) const
// Returns the index of the right child of node i.
{
   return 2 * i + 2;
}

template <typename T>
T heap<T>::getItem(int n) const
// Returns the nth element stored in the heap.
{
   return data[n];
}

template <typename T>
void heap<T>::initializeMaxHeap(const vector<T> &items)
// Takes a vector of items, copies it into the heap's internal
// storage, and builds a valid max-heap out of it.
{
   data = items;
   buildMaxHeap();
}

template <typename T>
void heap<T>::maxHeapify(int i, int heapSize)
// Fixes the max-heap property at node i, assuming the left
// and right subtrees are already valid max-heaps. Swaps with
// the larger child and recurses if needed. heapSize controls
// how much of the vector is considered part of the heap.

// input: i is the index of the node to heapify
// heapsize is the number of element currently considered 
// part of the heap
{
   int l = left(i);
   int r = right(i);
   int largest = i;

   if (l < heapSize && data[l] > data[largest])
   {
      largest = l;
   }

   if (r < heapSize && data[r] > data[largest])
   {
      largest = r;
   }

   if (largest != i)
   {
      swap(data[i], data[largest]);
      maxHeapify(largest, heapSize);
   }
}

template <typename T>
void heap<T>::buildMaxHeap()
// Turns the unordered data vector into a valid max-heap.
// Starts from the last non-leaf and calls maxHeapify going up.
{
   int n = data.size();

   for (int i = n / 2 - 1; i >= 0; i--)
   {
      maxHeapify(i, n);
   }
}

template <typename T>
vector<T> heap<T>::heapsort()
// Sorts the data in ascending order. Repeatedly moves the max
// (root) to the end of the array and shrinks the heap by one,
// then re-heapifies. Returns the sorted vector.
{
   int heapSize = data.size();

   for (int i = heapSize - 1; i > 0; i--)
   {
      // move current max to the back
      swap(data[0], data[i]);
      heapSize--;

      // restore heap property on the smaller heap
      maxHeapify(0, heapSize);
   } 

   return data;
}

#endif