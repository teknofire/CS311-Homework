/*
 * ksarray.h
 *
 *  Created on: Feb 10, 2014
 *      Author: Will
 */

#ifndef KSARRAY_H_
#define KSARRAY_H_

#include <cstdlib>
#include <algorithm>

template <typename DataType>
class KSArray {
public:
	typedef std::size_t size_type;
	typedef DataType value_type;

	explicit KSArray(size_type size);
	KSArray(size_type size, value_type value);
	~KSArray();

	/* TODO: define copy ctor, use std::copy */

	size_type size();
	value_type * begin();
	value_type * end();

	value_type & operator[](size_type index);
	const value_type & operator[](size_type index) const;
private:
	size_type _size;
	value_type * _data;
};

KSArray<DataType>::KSArray(size_type size): _data(new value_type[size]), _size(size)
{

}

#endif /* KSARRAY_H_ */
