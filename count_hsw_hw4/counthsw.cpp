/*
 * counthsw.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: Will
 */

#include "counthsw.h"
#include <iostream>
#include <ctime>

Board::Board(Board::Coord size, Board::Coord hole, Board::Coord finish)
	: _size(size), _finish(finish), _nodes(_size.first * _size.second, 0),
	  _row_visit_counts(_size.second, 0), _col_visit_counts(_size.first,0)
{
	visit(hole);
}

/* Playing with seeing if there is a different set of steps we take that can help find orphaned nodes */
//std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,1), Coord(0,1), Coord(1, 1), Coord(1,0), Coord(1,-1), Coord(0, -1), Coord(-1,-1), Coord(-1, 0)};
//std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,0), Coord(0,1), Coord(1, 0), Coord(0,-1), Coord(-1,1), Coord(1, 1), Coord(1,-1), Coord(-1, -1)};
std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,0), Coord(1, 0), Coord(0,1), Coord(0,-1), Coord(-1,1), Coord(1, 1), Coord(1,-1), Coord(-1, -1)};

int Board::total_nodes()
{
	return (_size.first * _size.second) - 1;
}

int & Board::get(Board::Coord node)
{
	if (node.first < 0 || node.second < 0 || node.first >= _size.first || node.second >= _size.second)
		throw std::out_of_range("get :: give coordinates are out of range");

	return _nodes[node.first + (node.second * _size.first)];
}

bool Board::been_visited(Board::Coord node)
{
	return get(node) > 0;
}

bool Board::visit(Board::Coord node)
{
	++_col_visit_counts[node.first];
	++_row_visit_counts[node.second];
	get(node) = 1;

	if (_col_visit_counts[node.first] == _size.second)
	{
		//we filled up this column
		if (node.first > 0 && node.first < (_size.first-1) && _col_visit_counts[node.first-1] < _size.second && _col_visit_counts[node.first+1] < _size.second)
			return false;
	}

	if (_row_visit_counts[node.second] == _size.first)
	{
		//we filled up this row
		if (node.second > 0 && node.second < (_size.second-1) && _row_visit_counts[node.second-1] < _size.first && _row_visit_counts[node.second+1] < _size.first)
			return false;
	}

	return true;
}

void Board::unvisit(Board::Coord node)
{
	--_col_visit_counts[node.first];
	--_row_visit_counts[node.second];
	get(node) = 0;
}

bool Board::is_orphaned(Coord node)
{
	for(auto dir:adjacent_dirs)
	{
		Coord neighbor(node.first + dir.first, node.second + dir.second);
		try
		{
			if (!been_visited(neighbor))
				return false;
		}
		catch(std::out_of_range &e)
		{
			//just swallow it
		}
	}

	return true;
}

bool Board::has_orphaned()
{
	for(int x=0; x < _size.first; ++x)
		for(int y=0; y < _size.second; ++y)
		{
			Coord n(x,y);
			if(!been_visited(n) && is_orphaned(n))
				return true;
		}

	return false;
}

int Board::count_solutions(Board::Coord node, int nodes_left)
{
	try
	{
		if (been_visited(node))
			return 0;

		if (node == _finish)
			return (nodes_left == 1) ? 1 : 0;

		if (!visit(node))
		{
			// couldn't visit this node because it probably orphaned other nodes
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
		solutions += count_solutions(Coord(node.first + dir.first, node.second + dir.second), nodes_left - 1);
	}

	unvisit(node);

	return solutions;
}

int countHSW(int size_x, int size_y, int forbid_x, int forbid_y, int start_x, int start_y, int finish_x, int finish_y)
{
	Board::Coord start(start_x, start_y);
	Board::Coord size(size_x, size_y);
	Board::Coord forbid(forbid_x, forbid_y);
	Board::Coord finish(finish_x, finish_y);

	time_t starttime;
	time_t endtime;

	time(&starttime);
	int solutions = 0;

	Board b(size, forbid, finish);
	solutions += b.count_solutions(start, b.total_nodes());

	time(&endtime);
	std::cout << difftime(endtime, starttime) << " seconds to solve" << std::endl;

	return solutions;
}
