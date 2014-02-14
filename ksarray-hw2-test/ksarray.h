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

// KSArray template class
// Class invariants
// Preconditions
// 		if size is given it must be a valid value for std::site_t otherwise defaults to 10
//		if value give it must be  type as the initialized class template
// Requirements on Types:
// 		DataType must have operator<, operator=, operator==, operator!=
template <typename DataType>
class KSArray
{
public:
	typedef std::size_t size_type;
	typedef DataType value_type;

	explicit KSArray(size_type size = 10);
	KSArray(size_type size, value_type value);
	explicit KSArray(const KSArray<value_type> &rhs);

	~KSArray();

	size_type size() const;

	value_type * begin();
	value_type * end();
	const value_type * begin() const;
	const value_type * end() const;

	value_type & operator[](size_type index);
	const value_type operator[](size_type index) const;

	KSArray<value_type> & operator=(const KSArray<value_type> &rhs);

	bool operator==(const KSArray<value_type> &rhs) const;
	bool operator!=(const KSArray<value_type> &rhs) const;
	bool operator<(const KSArray<value_type> &rhs) const;
	bool operator<=(const KSArray<value_type> &rhs) const;
	bool operator>(const KSArray<value_type> &rhs) const;
	bool operator>=(const KSArray<value_type> &rhs) const;

private:
	size_type _size;
	value_type * _data;
};

/* Function Implementations */


template <typename DataType>
KSArray<DataType>::KSArray(KSArray<DataType>::size_type size): _size(size), _data(new value_type[size])
{

}

template <typename DataType>
KSArray<DataType>::KSArray(KSArray<DataType>::size_type size, KSArray<DataType>::value_type value): _size(size), _data(new value_type[size])
{
	for(auto it = begin(); it != end(); ++it)
	{
		*it = value;
	}
}

template <typename DataType>
KSArray<DataType>::KSArray(const KSArray<DataType> &rhs) : _size(rhs.size()), _data(new KSArray<DataType>::value_type[rhs.size()])
{
	std::copy(rhs.begin(), rhs.end(), _data);
}

template <typename DataType>
KSArray<DataType>::~KSArray()
{
	delete [] _data;
}

template <typename DataType>
KSArray<DataType> & KSArray<DataType>::operator=(const KSArray<DataType> &rhs)
{
	if (this != &rhs)
	{
		delete [] _data;
		_size = rhs.size();
		_data = new value_type[_size];

		std::copy(rhs.begin(), rhs.end(), _data);
	}
	return *this;
}

template <typename DataType>
typename KSArray<DataType>::value_type * KSArray<DataType>::end()
{
	return &_data[_size];
}

template <typename DataType>
const typename KSArray<DataType>::value_type * KSArray<DataType>::end() const
{
	return &_data[_size];
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
typename KSArray<DataType>::value_type & KSArray<DataType>::operator[](KSArray<DataType>::size_type index)
{
	return _data[index];
}

template <typename DataType>
const typename KSArray<DataType>::value_type KSArray<DataType>::operator[](KSArray<DataType>::size_type index) const
{
	return _data[index];
}

template <typename DataType>
bool KSArray<DataType>::operator==(const KSArray<DataType> &rhs) const
{
	if (_size == rhs._size)
	{
		auto lhs_iterator = begin();
		auto rhs_iterator = rhs.begin();

		/* check to see if we can find any lhs values that are lexically != rhs values */
		for(; lhs_iterator != end() && rhs_iterator != rhs.end(); ++lhs_iterator, ++rhs_iterator)
		{
			if (*lhs_iterator != *rhs_iterator)
				return false;
		}

		return true;
	}

	return false;
}

template <typename DataType>
bool KSArray<DataType>::operator!=(const KSArray<DataType> &rhs) const
{
	return !(*this == rhs);
}

template <typename DataType>
bool KSArray<DataType>::operator<(const KSArray<DataType> &rhs) const
{
	auto lhs_iterator = begin();
	auto rhs_iterator = rhs.begin();

	/* check to see if we can find any lhs values that are lexically > rhs values */
	for(; lhs_iterator != end() && rhs_iterator != rhs.end(); ++lhs_iterator, ++rhs_iterator)
	{
		if (*lhs_iterator != *rhs_iterator)
			return *lhs_iterator < *rhs_iterator;
	}
	return size() < rhs.size();
}


template <typename DataType>
bool KSArray<DataType>::operator>(const KSArray<DataType> &rhs) const
{
	return rhs < *this;
}

template <typename DataType>
bool KSArray<DataType>::operator>=(const KSArray<DataType> &rhs) const
{
	return !(*this < rhs);
}

template <typename DataType>
bool KSArray<DataType>::operator<=(const KSArray<DataType> &rhs) const
{
	return !(rhs < *this);
}


template <typename DataType>
typename KSArray<DataType>::size_type KSArray<DataType>::size() const
{
	return _size;
}

#endif /* KSARRAY_H_ */
