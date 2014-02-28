// da3.h (Skeleton)
// Chris Hartman
// 2/12/2010
// 
// based on material by
// Glenn G. Chappell
// 25 Sep 2009
// 
// For CS 311 Spring 2010
// Header file for Assignment 3

#ifndef FILE_DA3_H_INCLUDED
#define FILE_DA3_H_INCLUDED

#include <iostream>   // for std::ostream
#include <string>     // for std::string
#include <iterator>	  // for std::ostream_iterator
#include <algorithm>  // for std::copy


// *************************************************************** // *
// Begin DO-NOT-CHANGE section                                     // *
// Do not alter the lines below                                    // *
// *************************************************************** // *
                                                                   // *
                                                                   // *
// struct LLNode                                                   // *
// Linked List node, with client-specified value type              // *
// Invariants:                                                     // *
//     Either next_ is NULL, or next_ points to an LLNode,         // *
//      allocated with new, owned by *this.                        // *
template <typename ValueType>                                      // *
struct LLNode {                                                    // *
    ValueType data_;  // Data for this node                        // *
    LLNode * next_;   // Ptr to next node, or NULL if none         // *
                                                                   // *
    // The following simplify creation & destruction               // *
                                                                   // *
    // 1- & 2-param ctor                                           // *
    // Pre:                                                        // *
    //     theNext, if passed, is either NULL,                     // *
    //      or else it points to an LLNode, allocated with new,    // *
    //      with ownership transferred to *this.                   // *
    // Post:                                                       // *
    //     data_ == theData.                                       // *
    //     If next_ passed, then next_ == theNext.                 // *
    //      otherwise, next_ is NULL.                              // *
    explicit LLNode(const ValueType & theData,                     // *
                    LLNode * theNext = NULL)                       // *
        :data_(theData), next_(theNext)                            // *
    {}                                                             // *
                                                                   // *
    // dctor                                                       // *
    // Pre: None.                                                  // *
    // Post: None. (next_ delete'd)                                // *
    ~LLNode()                                                      // *
    { delete next_; }                                              // *
};                                                                 // *
                                                                   // *
                                                                   // *
// *************************************************************** // *
// End DO-NOT-CHANGE section                                       // *
// Do not alter the lines above                                    // *
// *************************************************************** // *



template <typename T>
T listItem(const LLNode<T> * head,
           int index)
{
	auto node = head;
	int count = 0;

	while(node != NULL) {
		if (count == index)
			return node->data_;
		else {
			node = node->next_;
			++count;
		}
	}

	throw std::out_of_range("listItem :: given index is out of range");
}


template <typename Func>
void didItThrow(Func f,
                bool & threw)
{
	threw = false;
	try {
		f();
	}
	catch(...) {
		threw = true;
		throw;
	}
}

template <typename FDIter>
void printRange(FDIter first,
                FDIter last,
                std::ostream & theStream)
{
	for(auto iter = first; iter != last; ++iter)
		theStream << *iter << "\n";
}

/*
 * rangesEqual
 * Preconditions:
 * 		first1 comes before last1 and can reach last1
 * Postconditions:
 * 		returns true if the values in ranges first1..last1 match values starting at first2
 * 		returns false otherwise
 */
template <typename FDIter>
bool rangesEqual(FDIter first1,
                 FDIter last1,
                 FDIter first2)
{
	return std::equal(first1, last1, first2);
}

//defined in da3.cpp
int collatz(int n);

#endif  //#ifndef FILE_DA3_H_INCLUDED

