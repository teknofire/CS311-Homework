/*
 * ksarray.h
 *
 *  Created on: Feb 10, 2014
 *      Author: Will Fisher
 *      Description: Template class for kinda smart array container
 */

#ifndef KSARRAY_H_
#define KSARRAY_H_

#include <cstdlib>
#include <algorithm>

// KSArray template class
// Class invariants
// 		size >= 0
//      _data points to an array of items of the given type allocated with new, owned by *this
// Requirements on Types:
// 		ValueType must have operator<, operator=, operator==, operator!=
template <typename ValueType>
class KSArray
{
public:
	typedef std::size_t size_type;
	typedef ValueType value_type;

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

private:
	size_type _size;
	value_type * _data;
};

template <typename ValueType>
bool operator==(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs);

template <typename ValueType>
bool operator!=(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs);

template <typename ValueType>
bool operator<(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs);

template <typename ValueType>
bool operator<=(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs);

template <typename ValueType>
bool operator>(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs);

template <typename ValueType>
bool operator>=(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs);

/* Function Implementations */

// Constructor
// Preconditions
//    Must satisfy class invariants
template <typename ValueType>
KSArray<ValueType>::KSArray(KSArray<ValueType>::size_type size): _size(size), _data(new value_type[size])
{

}

// Constructor with initialization value
// Preconditions
//    Must satisfy class invariants
// Postconditions
//    _data items will be initialized with the given value
template <typename ValueType>
KSArray<ValueType>::KSArray(KSArray<ValueType>::size_type size, KSArray<ValueType>::value_type value): _size(size), _data(new value_type[size])
{
	for(auto it = begin(); it != end(); ++it)
	{
		*it = value;
	}
}

// Copy Constructor
// Preconditions
//    Must satisfy class invariants
// Postconditions
//    makes a copy of rhs
template <typename ValueType>
KSArray<ValueType>::KSArray(const KSArray<ValueType> &rhs) : _size(rhs.size()), _data(new KSArray<ValueType>::value_type[rhs.size()])
{
	std::copy(rhs.begin(), rhs.end(), _data);
}

// Destructor
// Preconditions
//    None
// Postconditions
//    frees up allocated memory
template <typename ValueType>
KSArray<ValueType>::~KSArray()
{
	delete [] _data;
}

// operator=
// Preconditions
//   None
// Postconditions
//   makes *this a copy of rhs
template <typename ValueType>
KSArray<ValueType> & KSArray<ValueType>::operator=(const KSArray<ValueType> &rhs)
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

// end
// Preconditions
//    None
// Postconditions
//    returns ptr to the end of the array
template <typename ValueType>
typename KSArray<ValueType>::value_type * KSArray<ValueType>::end()
{
	return &_data[_size];
}

// end (const)
// Preconditions
//    None
// Postconditions
//    returns ptr to the end of the array
template <typename ValueType>
const typename KSArray<ValueType>::value_type * KSArray<ValueType>::end() const
{
	return &_data[_size];
}

// begin
// Preconditions
//    None
// Postconditions
//    returns ptr to the beginning of the array
template <typename ValueType>
typename KSArray<ValueType>::value_type * KSArray<ValueType>::begin()
{
	return &_data[0];
}

// begin (const)
// Preconditions
//    None
// Postconditions
//    returns a ptr to the beginning of the array, value cannot be changed.
template <typename ValueType>
const typename KSArray<ValueType>::value_type * KSArray<ValueType>::begin() const
{
	return &_data[0];
}

// operator[]
// Preconditions
//    0 <= index >= this->size()
// Postconditions
//    returns a reference to value at the given position in the array
template <typename ValueType>
typename KSArray<ValueType>::value_type & KSArray<ValueType>::operator[](KSArray<ValueType>::size_type index)
{
	return _data[index];
}

// operator [] const
// Preconditions
//    0 <= index >= this->size()
// Postconditions
//    returns the value at the given position in the array, cannot be modified.
template <typename ValueType>
const typename KSArray<ValueType>::value_type KSArray<ValueType>::operator[](KSArray<ValueType>::size_type index) const
{
	return _data[index];
}

// operator==
// Preconditions
//    None
// Postconditions
//    returns true if the size and values of the arrays are the same
//    returns false otherwise
template <typename ValueType>
bool operator==(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs)
{
	if (lhs.size() == rhs.size())
	{
		auto lhs_iterator = lhs.begin();
		auto rhs_iterator = rhs.begin();

		/* check to see if we can find any lhs values that are lexically != rhs values */
		for(; lhs_iterator != lhs.end() && rhs_iterator != rhs.end(); ++lhs_iterator, ++rhs_iterator)
		{
			if (*lhs_iterator != *rhs_iterator)
				return false;
		}

		return true;
	}

	return false;
}

// operator!=
// Preconditions
//    None
// Postconditions
//    return true if lhs != rhs
//    return false otherwise
template <typename ValueType>
bool operator!=(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs)
{
	return !(lhs == rhs);
}

// operator<
// Preconditions
//    None
// Postconditions
//    return true if lhs lexically < rhs
//    return true if lhs == rhs and lhs size < rhs size
//    return false otherwise
template <typename ValueType>
bool operator<(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs)
{
	auto lhs_iterator = lhs.begin();
	auto rhs_iterator = rhs.begin();

	for(; lhs_iterator != lhs.end() && rhs_iterator != rhs.end(); ++lhs_iterator, ++rhs_iterator)
	{
		if (*lhs_iterator != *rhs_iterator)
			return *lhs_iterator < *rhs_iterator;
	}
	return lhs.size() < rhs.size();
}

// operator>
// Preconditions
//    None
// Postconditions
//    return true if lhs lexically > rhs
//    return true if lhs == rhs and lhs size > rhs size
//    return false otherwise
template <typename ValueType>
bool operator>(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs)
{
	return rhs < lhs;
}

// operator>=
// Preconditions
//    None
// Postconditions
//    return true if lhs >= rhs
//    return false otherwise
template <typename ValueType>
bool operator>=(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs)
{
	return !(lhs < rhs);
}

// operator<=
// Preconditions
//    None
// Postconditions
//    return true if lhs <= rhs
//    return false otherwise
template <typename ValueType>
bool operator<=(const KSArray<ValueType> &lhs, const KSArray<ValueType> &rhs)
{
	return !(rhs < lhs);
}

// size
// Preconditions
//    None
// Postconditions
//    returns the size of the array
template <typename ValueType>
typename KSArray<ValueType>::size_type KSArray<ValueType>::size() const
{
	return _size;
}

#endif /* KSARRAY_H_ */
