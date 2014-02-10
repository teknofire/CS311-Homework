/*
 * IntArray.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: Will
 */

#include "IntArray.h"

// note the value_type
IntArray::IntArray(size_type size) : _data(new value_type[size]) {

}

IntArray::~IntArray() {
	delete _data;
}

IntArray::value_type & IntArray::operator [](size_type index) {
	return _data[index];
}

const IntArray::value_type & IntArray::operator [](size_type index) const {
	return _data[index];
}

int main() {
	IntArray x(6);
	x[5] = 6;
	const IntArray y(25);
//	Should error out
//	y[5] = 7;
}
