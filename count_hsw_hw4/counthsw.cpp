/*
 * counthsw.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: Will
 */

#include "counthsw.h"
#include <iostream>
#include <ctime>

Board::Board(Board::Coord size, Board::Coord hole, Board::Coord start, Board::Coord finish): _size(size), _hole(hole), _start(start), _finish(finish), _nodes(_size.first * _size.second, 0)
{
	visit(hole);
	// are we dealing with a large board (more than 19 spots and at least 3 on each side)
	_large_board = (total_nodes() >= 19 && _size.first > 3 && _size.second > 3);
}

/* Playing with seeing if there is a different set of steps we take that can help find orphaned nodes */
//std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,1), Coord(0,1), Coord(1, 1), Coord(1,0), Coord(1,-1), Coord(0, -1), Coord(-1,-1), Coord(-1, 0)};
std::vector<Board::Coord> Board::adjacent_dirs = {Coord(-1,0), Coord(0,1), Coord(1, 0), Coord(0,-1), Coord(-1,1), Coord(1, 1), Coord(1,-1), Coord(-1, -1)};

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

void Board::visit(Board::Coord node)
{
	get(node) = 1;
}

void Board::unvisit(Board::Coord node)
{
	get(node) = 0;
}

std::vector<Board::Coord> Board::find_adjacent_nodes(Board::Coord node)
{
	std::vector<Coord> nbs;

	for(auto dir:adjacent_dirs)
	{
		try
		{
			Coord neighbor(node.first + dir.first, node.second + dir.second);

			if (!been_visited(neighbor))
				nbs.push_back(neighbor);
		}
		catch(std::out_of_range &e)
		{
			//just swallow it
		}
	}

	return nbs;
}

int Board::distance_to_finish(Coord node)
{
	auto a = abs(node.first - _finish.first);
	auto b = abs(node.second - _finish.second);
	return (a<b) ? b : a;
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
	if (node == _finish)
		return (nodes_left == 1) ? 1 : 0;

	//if we are near the finish make sure we didn't orphan it
	//make sure we also check for orphaned nodes BEFORE visiting the current node
	//this way we don't mistakenly think the last _finish node is orphaned at the end
	//of a solution
	if (distance_to_finish(node) == 2 && is_orphaned(_finish))
		throw OrphanedNode();

	static int part_way = total_nodes()/4+10;
	if ((nodes_left % part_way == 0) && has_orphaned())
		throw OrphanedNode();

	int solutions = 0;
	visit(node);

	for(auto dir:adjacent_dirs)
	{
		try
		{
			Coord neighbor(node.first + dir.first, node.second + dir.second);
			if (!been_visited(neighbor))
			{
				try
				{
					solutions += count_solutions(neighbor, nodes_left - 1);
				}
				catch(OrphanedNode &e)
				{
					//roll back till there isn't an orphaned node
					unvisit(neighbor);
					if(has_orphaned())
						throw OrphanedNode();
				}
				unvisit(neighbor);
			}
		}
		catch(std::out_of_range &e)
		{
			//just swallow it, just move on to the next item
		}
	}

	return solutions;
}

int countHSW(int size_x, int size_y, int forbid_x, int forbid_y, int start_x, int start_y, int finish_x, int finish_y)
{
	Board::Coord start(start_x, start_y);
	Board::Coord size(size_x, size_y);
	Board::Coord forbid(forbid_x, forbid_y);
	Board::Coord finish(finish_x, finish_y);

	Board b(size, forbid, start, finish);
//	time_t starttime;
//	time_t endtime;
//
//	time(&starttime);
	int solutions = 0;

	try
	{
		solutions += b.count_solutions(start, b.total_nodes());
	}
	catch(OrphanedNode &e)
	{
		//orphaned right off the bat!
	}

//	time(&endtime);
//	std::cout << difftime(endtime, starttime) << " seconds to solve" << std::endl;
//
	return solutions;
}
