/*
 * birthday.cpp
 *
 *  Created on: Jan 31, 2014
 *      Author: Will Fisher
 */

#include "birthday.h"
#include <sstream>
using std::ostringstream;

// Birthday
// Birthday class default constructor
// Pre: 
//   must satisfy class invariants if values are given
// Post:
//   if no values are given sets name to "" and sets birthday to January 1
Birthday::Birthday(string name, int month, int day)
	:_name(name),_month(month),_day(day)
{
}

// Initialize the list of month abbreviations
const string Birthday::_month_abbreviations[12] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// getName
// Pre: 
//   none
// Post:
//   returns the name of the birthday person
string Birthday::getName() const {
	return _name;
}

// getMonth
// Pre: 
//   none
// Post:
//   returns the number representation of the birthday month
int Birthday::getMonth() const {
	return _month;
}

// getDay
// Pre: 
//   none
// Post:
//   returns the day of the month for the birthday
int Birthday::getDay() const {
	return _day;
}

// setName
// Pre: 
//   must satisfy class invariants
// Post:
//   sets the name to the given value
void Birthday::setName(const string name) {
	_name = name;
}

// setMonth
// Pre: 
//   must satisfy class invariants
// Post:
//   sets the month to the given value
void Birthday::setMonth(const int month) {
	_month = month;
}

// setDay
// Pre: 
//   must satisfy class invariants
// Post:
//   set the day to the given value
void Birthday::setDay(const int day) {
	_day = day;
}

// toString
// Pre: 
//   none
// Post:
//   returns a human readable format of the class instance in the format: {name} ({month abbreviation} {day}) 
//   example: Will Fisher (Nov 6)
string Birthday::toString() const {
	ostringstream output;
	output << getName() << " (" << getMonthAbbr() << " " << getDay() << ")";
	return output.str();
}

// getMonthAbbr
// Pre: 
//   none
// Post:
//   returns the 3 letter abbreviation for a month
string Birthday::getMonthAbbr() const {
	return _month_abbreviations[(getMonth()-1)];
}

// operator==
// Pre: 
//   none
// Post:
//   returns true if lhs is equal to rhs
bool operator ==(const Birthday& lhs, const Birthday& rhs) {
	return (lhs._name == rhs._name && lhs._month == rhs._month && lhs._day == rhs._day);
}

// operator!=
// Pre: 
//   none
// Post:
//   returns true if lhs is not equal to rhs
bool operator!=(const Birthday& lhs, const Birthday& rhs)
{
  return !(lhs == rhs);
}

// operator<<
// Pre: 
//   os is not in an error state
// Post:
//   toprint has been printed in human format to os
ostream& operator<<(ostream& os, const Birthday& toprint)
{
  return os << toprint.toString();
}

