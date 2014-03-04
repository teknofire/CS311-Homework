// da3.cpp (HW3 assignment for CS311)
// Will Fisher
// 02/24/2014
//
// da3.cpp (skeleton)
// Chris Hartman
// 2/12/2010
// 
// based on material by
// Glenn G. Chappell
// 25 Sep 2009
// 
// For CS 311 Spring 2010
// Source file for Assignment 3

#include "da3.h"

/*
 * Precodition:
 * 		0 < n < max value of int
 * Postcondition:
 * 		returns the number of steps required to get to n == 1
 *      Does not throw
 */
int collatz(int n)
{
	if (n == 1) {
		return 0;
	}

	if (n % 2 == 0)
		n =  n / 2;
	else
		n = 3*n+1;

	return 1 + collatz(n);
}
