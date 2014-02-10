/*
 * IntArray.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Will
 */

#ifndef INTARRAY_H_
#define INTARRAY_H_

#include <cstdlib>

// class IntArray
// Invariants
// 		_data points to an array of int allocated with new, owned by *this
class IntArray {
public:
	typedef std::size_t size_type;
	typedef int value_type;

	explicit IntArray(size_type size);
	~IntArray();

	value_type & operator[](size_type index);
	const value_type & operator[](size_type index) const;
private:
	value_type * _data;
};

#endif /* INTARRAY_H_ */
