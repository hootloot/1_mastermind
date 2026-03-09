// File: d_node.h
// Names: Ryan Kim, Maddox Grillo-Smith, Vishnu Kumar, Preeth Somanchi
// Assignment: Project Flip cards part a

#ifndef NODE_CLASS
#define NODE_CLASS

#ifndef NULL
#include <cstddef>
#endif  // NULL

// linked list node
template <typename T>
class node
{
   public:
      T nodeValue;      // data held by the node
      node<T> *next;    // next node in the list

      // default constructor with no initial value
      node() : next(NULL)
      {}

      // constructor. initialize nodeValue and next
      node(const T& item, node<T> *nextNode = NULL) : 
			  nodeValue(item), next(nextNode)
      {}
};

#endif   // NODE_CLASS
