//
//  ksarray.h
//  ksarray-hw2
//
//  Created by Will Fisher on 2/10/14.
//  Copyright (c) 2014 Will Fisher. All rights reserved.
//

#ifndef KSARRAY_H_
#define KSARRAY_H_

#include <cstdlib>
#include <algorithm>

template <typename DataType>
class KSArray
{
	friend bool operator==(const KSArray<DataType> &lhs, const KSArray<DataType> &rhs);
	friend bool operator!=(const KSArray<DataType> &lhs, const KSArray<DataType> &rhs);

public:
	typedef std::size_t size_type;
	typedef DataType value_type;

	explicit KSArray(size_type size=10);
	KSArray(size_type size, value_type value);
	KSArray(const KSArray<DataType> &rhs);
	~KSArray();

	/* TODO: define copy ctor, use std::copy */

	size_type size() const;
	value_type * begin();
	value_type * end();
	const value_type * begin() const;
	const value_type * end() const;

	value_type & operator[](size_type index);
	const value_type operator[](size_type index) const;
	KSArray<value_type> & operator=(const KSArray<value_type> &rhs);

	bool operator<(const KSArray<value_type> &rhs);
	bool operator<=(const KSArray<value_type> &rhs);
	bool operator>(const KSArray<value_type> &rhs);
	bool operator>=(const KSArray<value_type> &rhs);

private:
	size_type _size;
	value_type * _data;
};

/* global operator defs */

template <typename DataType>
bool operator==(const KSArray<DataType> &lhs, const KSArray<DataType> &rhs);

template <typename DataType>
bool operator!=(const KSArray<DataType> &lhs, const KSArray<DataType> &rhs);

/* Class function implementations */

template <typename DataType>
KSArray<DataType>::KSArray(size_type size): _size(size), _data(new value_type[size])
{

}

template <typename DataType>
KSArray<DataType>::KSArray(size_type size, value_type value): _size(size), _data(new value_type[size])
{
	for(auto it = begin(); it < end(); ++it)
	{
		*it = value;
	}
}

template <typename DataType>
KSArray<DataType>::~KSArray()
{
	delete [] _data;
}

// copy ctor
template <typename DataType>
KSArray<DataType>::KSArray(const KSArray<DataType> &rhs) : _size(rhs.size()), _data(new value_type[rhs.size()])
{
	operator=(rhs);
}

template <typename DataType>
typename KSArray<DataType>::value_type & KSArray<DataType>::operator[](size_type index)
{
    return _data[index];
}

template <typename DataType>
const typename KSArray<DataType>::value_type KSArray<DataType>::operator[](size_type index) const
{
    return _data[index];
}


template <typename DataType>
bool operator==(const KSArray<DataType> &lhs, const KSArray<DataType> &rhs) {
	return (lhs._size == rhs._size && lhs._data == rhs._data);
}

template <typename DataType>
bool operator!=(const KSArray<DataType> &lhs, const KSArray<DataType> &rhs) {
	return !(lhs == rhs);
}


template <typename DataType>
bool KSArray<DataType>::operator<(const KSArray<DataType> &rhs)
{
	auto lh_it = begin();
	auto rh_it = rhs.begin();


	return *lh_it < *rh_it;
}

template <typename DataType>
bool KSArray<DataType>::operator<=(const KSArray<DataType> &rhs)
{
	return false;
}

template <typename DataType>
bool KSArray<DataType>::operator>(const KSArray<DataType> &rhs)
{
	return false;
}

template <typename DataType>
bool KSArray<DataType>::operator>=(const KSArray<DataType> &rhs)
{
	return false;
}

//operator=
template <typename DataType>
KSArray<DataType> & KSArray<DataType>::operator=(const KSArray<DataType> &rhs)
{
	if (this != &rhs)
	{
		delete [] _data;
		_data = new value_type[_size];

		std::copy(rhs.begin(), rhs.end(), _data);
	}

	return *this;
}

template <typename DataType>
typename KSArray<DataType>::value_type * KSArray<DataType>::begin()
{
	return &_data[0];
}

template <typename DataType>
const typename KSArray<DataType>::value_type * KSArray<DataType>::begin() const
{
	return &_data[0];
}

template <typename DataType>
const typename KSArray<DataType>::value_type * KSArray<DataType>::end() const
{
	return &_data[_size];
}

template <typename DataType>
typename KSArray<DataType>::value_type * KSArray<DataType>::end()
{
	return &_data[_size];
}


template <typename DataType>
typename KSArray<DataType>::size_type KSArray<DataType>::size() const
{
	return _size;
}

#endif /* KSARRAY_H_ */
