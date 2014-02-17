/*
 * binsearch.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: Will
 */

#include <iostream>

template <typename RAIter, typename ValueType>
bool binSearch1(RAIter first, RAIter last, const ValueType & findMe)
{
	if (first == last)
		return false;
	if (first == last-1)
		return *first == findMe;

	RAIter pivot = first + (last-first)/2;

	if(findMe < *pivot)
		return binSearch1(first, pivot, findMe);
	else
		return binSearch1(pivot, last, findMe);
}

int main(void)
{
	const int SIZE=100;
	int arr[SIZE];
	for(int i=0;i < SIZE; ++i)
		arr[i] = 10*i;

	int value = 41;
	bool success;

	success = binSearch1(arr, arr+SIZE, value);
	std::cout << value << " found? " << success << std::endl;

	value = 70;
	success = binSearch1(arr, arr+SIZE, value);
	std::cout << value << " found? " << success << std::endl;

	return 0;
}
