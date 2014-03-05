/*
 * counthsw.h
 * Purpose: header file for counthsw homework #4
 *
 *  Created on: Feb 28, 2014
 *      Author: Will Fisher
 */

#ifndef COUNTHSW_H_
#define COUNTHSW_H_

#include <vector>
#include <utility>   // for std::pair
#include <stdexcept> // for std::out_of_range
#include <algorithm>
#include <string>

// Board class
// Class invariants
//    _size.first and size.second > 0
//    _hole must be within the bounds of the board (0..size)
//    _finish must be within the bounds of the board (0..size)
//	  _hole & _finish must be different points on the board
class Board {
public:
	typedef std::pair<int,int> Coord;

	Board(Coord size, Coord hole, Coord finish);
	// no default ctor
	// using silently written copy ctor, copy assignment, and dtor

	int total_nodes();
	int countHSW_recurse(Coord node, int nodes_left);
	int & get(Coord node);
	bool been_visited(Coord node);
	void visit(Coord node);
	void unvisit(Coord node);
	bool is_orphaned(Coord node);
	bool column_orphaned_near(Coord node);
	bool row_orphaned_near(Coord node);
	bool has_orphaned();


	Coord _size;
	Coord _finish;

	static std::vector<Coord> adjacent_dirs;
	std::vector<int> _nodes;
	std::vector<int> _row_visit_counts;
	std::vector<int> _col_visit_counts;
};

int countHSW(int size_x, int size_y, int forbid_x, int forbid_y, int start_x, int start_y, int finish_x, int finish_y);

#endif /* COUNTHSW_H_ */
