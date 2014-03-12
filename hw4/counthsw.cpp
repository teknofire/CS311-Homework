/*
 * counthsw.cpp
 * Purpose: implementation file for counthsw homework #4
 *
 *  Created on: Feb 28, 2014
 *      Author: Will Fisher
 */

#include "counthsw.h"
#include <iostream>

/* Board constructor
 *
 * Preconditions:
 * 	none
 * Postconditions:
 * 	none
 */
Board::Board(Board::Coord size, Board::Coord hole, Board::Coord finish)
	: _size(size), _finish(finish), _nodes(_size.first * _size.second, 0),
	  _row_visit_counts(_size.second, 0), _col_visit_counts(_size.first,0)
{
	visit(hole);
}

/* static Board::adjacent_dirs
 * static list of directions used to find neighboring nodes
 * Playing with different orderings to seeing if can help find orphaned nodes quicker
 */
//const std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,1), Coord(0,1), Coord(1, 1), Coord(1,0), Coord(1,-1), Coord(0, -1), Coord(-1,-1), Coord(-1, 0)};
//const std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,0), Coord(0,1), Coord(1, 0), Coord(0,-1), Coord(-1,1), Coord(1, 1), Coord(1,-1), Coord(-1, -1)};
const std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,0), Coord(1, 0), Coord(0,1), Coord(0,-1), Coord(-1,1), Coord(1, 1), Coord(1,-1), Coord(-1, -1)};

/* total_nodes
 * Preconditions:
 * 	none
 * Postconditions:
 * 	returns the total # of valid nodes for the board
 */
int Board::total_nodes()
{
	return (_size.first * _size.second) - 1;
}

/* get
 * Preconditions:
 * 	node is within the bounds of the board
 * Postconditions:
 * 	return state of the give node (0 = unvisited, >1 = visited)
 * 	will throw std::out_of_range if an invalid node is given
 */
int & Board::get(const Board::Coord & node)
{
	if (!valid_node(node))
		throw std::out_of_range("get :: give coordinates are out of range");

	return _nodes[node.first + (node.second * _size.first)];
}

bool Board::valid_node(const Board::Coord & node)
{
	return !(node.first < 0 || node.second < 0 || node.first >= _size.first || node.second >= _size.second);
}

/*
 * been_visited
 * Preconditions:
 * 	node is within the bounds of the board
 * Postconditions:
 * 	return true if we have previously visited the given node
 */
bool Board::been_visited(const Board::Coord & node)
{
	return get(node) > 0;
}

/*
 * column_orphaned_near
 * Preconditions:
 * 	node is within the bounds of the board
 * Postconditions:
 * 	returns false if we created any orphaned columns near node
 * 	returns true otherwise
 */
bool Board::column_orphaned_near(const Board::Coord & node)
{
	return _col_visit_counts[node.first] == _size.second && node.first > 0 &&
			node.first < (_size.first-1) && _col_visit_counts[node.first-1] < _size.second &&
			_col_visit_counts[node.first+1] < _size.second;
}

/*
 * row_orphaned_near
 * Preconditions:
 * 	node is within the bounds of the board
 * Postconditions:
 * 	returns false if there are any orphaned rows near node
 * 	returns true otherwise
 */
bool Board::row_orphaned_near(const Board::Coord & node)
{
	return _row_visit_counts[node.second] == _size.first && node.second > 0 &&
			node.second < (_size.second-1) && _row_visit_counts[node.second-1] < _size.first &&
			_row_visit_counts[node.second+1] < _size.first;
}

/*
 * visit
 * Preconditions:
 * 	node is within the bounds of the board
 * Postconditions:
 * 	none
 */
void Board::visit(const Board::Coord & node)
{
	++_col_visit_counts[node.first];
	++_row_visit_counts[node.second];
	get(node) = 1;
}

/*
 * unvisit
 * Preconditions:
 * 	node is within the bounds of the board
 * Postconditions:
 * 	none
 */
void Board::unvisit(const Board::Coord & node)
{
	--_col_visit_counts[node.first];
	--_row_visit_counts[node.second];
	get(node) = 0;
}

/*
 * countHSW_recurse
 * Preconditions:
 * 	node is within the bounds of the board
 * 	0 < nodes_left <= total_nodes()
 * Postconditions:
 * 	returns the number of solutions that start with the given node
 */
int Board::countHSW_recurse(const Board::Coord & node, int nodes_left)
{
	try
	{
		if (been_visited(node))
			return 0;

		if (node == _finish)
			return (nodes_left == 1) ? 1 : 0;

		visit(node);

		if (column_orphaned_near(node) || row_orphaned_near(node))
		{
			unvisit(node);
			return 0;
		}
	}
	catch(std::out_of_range &e)
	{
		return 0;
	}

	int solutions = 0;
	for(auto dir:adjacent_dirs)
	{
		Coord next(node.first + dir.first, node.second + dir.second);
		if(valid_node(next))
			solutions += countHSW_recurse(next, nodes_left - 1);

	}

	unvisit(node);

	return solutions;
}

/*
 * countHSW helper method
 *  may throw bad_alloc
 * Preconditions:
 * 	0 < size_(x|y)
 * 	0 < forbid_(x|y)
 * 	0 < start_(x|y)
 * 	0 < finish_(x|y)
 * 	forbid_(x|y), start_(x|y) and finish_(x|y) must always be distinct locations on the board
 * Postconditions:
 * 	returns the number of holey spider walk solutions for the given board params
 */
int countHSW(int size_x, int size_y, int forbid_x, int forbid_y, int start_x, int start_y, int finish_x, int finish_y)
{
	Board::Coord start(start_x, start_y);
	Board::Coord size(size_x, size_y);
	Board::Coord forbid(forbid_x, forbid_y);
	Board::Coord finish(finish_x, finish_y);

	Board b(size, forbid, finish);
	return b.countHSW_recurse(start, b.total_nodes());
}
