/*
 * binsearch.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: Will
 */

#include <iostream>
#include <iterator>

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

template <typename FDIter, typename ValueType>
bool binSearch2(FDIter first, FDIter last, const ValueType & findMe)
{
	std::size_t dist = std::distance(first, last);

	if (dist == 0)
		return false;
	if (dist == 1)
		return !(*first < findMe) && !(findMe < *first);

	FDIter pivot = first + (last-first)/2;

	if(findMe < *pivot)
		return binSearch1(first, pivot, findMe);
	else
		return binSearch1(pivot, last, findMe);
}

template <typename FDIter, typename ValueType>
bool binSearch3(FDIter first, FDIter last, const ValueType & findMe)
{
	while(true) {
		std::size_t dist = std::distance(first, last);

		if (dist == 0)
			return false;
		if (dist == 1)
			return !(*first < findMe) && !(findMe < *first);

		FDIter pivot = first;
		std::advance(pivot,dist/2);

		if(findMe < *pivot) {
			last = pivot;
		}
		else {
			first = pivot;
		}
	}
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
	std::cout << value << "search1 found? " << success << std::endl;

	value = 70;
	success = binSearch1(arr, arr+SIZE, value);
	std::cout << value << "search1 found? " << success << std::endl;

	value = 41;
	success = binSearch2(arr, arr+SIZE, value);
	std::cout << value << "search2 found? " << success << std::endl;

	value = 70;
	success = binSearch2(arr, arr+SIZE, value);
	std::cout << value << "search2 found? " << success << std::endl;

	value = 41;
	success = binSearch3(arr, arr+SIZE, value);
	std::cout << value << "search3 found? " << success << std::endl;

	value = 70;
	success = binSearch3(arr, arr+SIZE, value);
	std::cout << value << "search3 found? " << success << std::endl;


	return 0;
}
