/*
 * nqueens.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: Will
 */


#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

typedef vector<int> Board;

void printSolution(Board b)
{

}

bool isOk(Board b)
{
	return true;
}

void workhorse(Board b, int n)
{
	if (b.size() == n) {
		printSolution(b);
	}
	else {
		for(unsigned int i=0;i<n;++i)
		{
			Board newboard(b);
			newboard.push_back(i);
			if (isOk(newboard))
				workhorse(newboard, n);
		}
	}
}

void nQueens(int n)
{
	workhorse(vector<int>(), n);
}

int main()
{
	nQueens(4);
	return 0;
}
