/*
 * birthday.h
 *
 *  Created on: Jan 31, 2014
 *      Author: Will Fisher
 */

#ifndef BIRTHDAY_H_
#define BIRTHDAY_H_

#include <string>
using std::string;
#include <iostream>
using std::ostream;

//Class invariants
//Preconditions:
//  1 <= _month <= 12
//  _day must be a valid date in the given month, (January only has 31 days, etc...)
class Birthday
{
friend bool operator==(const Birthday &lhs, const Birthday &rhs);
friend bool operator!=(const Birthday &lhs, const Birthday &rhs);

public:
	Birthday(string name="", int month=1, int day=1);
  //using sliently written copy ctr, copy assignment, and dtor
  
	string getName() const;
	int getMonth() const;
	int getDay() const;
	void setName(const string name);
	void setMonth(const int month);
	void setDay(const int day);

	string toString() const;
private:
	string _name;
	int _month;
	int _day;
	string _month_abbreviations[12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	/*                          Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec */
	int _days_per_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	string getMonthAbbr() const;
};

bool operator==(const Birthday &lhs, const Birthday &rhs);
bool operator!=(const Birthday &lhs, const Birthday &rhs);
ostream & operator<<(ostream &, const Birthday &toprint);

#endif /* BIRTHDAY_H_ */
