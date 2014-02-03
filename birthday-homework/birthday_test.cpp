// birthday_test.cpp
// Chris Hartman, 1/26/2010
// minor modifications from original:
// Glenn G. Chappell
// 11 Sep 2009
//
// For CS 311 Fall 2010
// Test program for class Birthday
// Used in Assignment 1, Exercise A

// Includes for code to be tested
#include "birthday.h"   // For class Birthday
#include "birthday.h"   // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <sstream>      // for std::ostringstream


// ************************************************************************
// Testing Package:
//     Class Tester - For Tracking Tests
// ************************************************************************


// class Tester
// For extremely simple unit testing.
// Keeps track of number of tests and number of passes.
// Use test (with success/failure parameter) to do a test.
// Get results with numTests, numPassed, numFailed, allPassed.
// Restart testing with reset.
// Invariants:
//     countTests_ == number of tests (calls to test) since last reset.
//     countPasses_ == number of times function test called with true param
//      since last reset.
//     0 <= countPasses_ <= countTests_.
//     tolerance_ >= 0.
class Tester {

// ***** Tester: ctors, dctor, op= *****
public:

    // Default ctor
    // Sets countTests_, countPasses_ to zero, tolerance_ to given value
    // Pre: None.
    // Post:
    //     numTests == 0, countPasses == 0, tolerance_ == abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    Tester(double theTolerance = 0.0000001)
        :countTests_(0),
         countPasses_(0),
         tolerance_(theTolerance >= 0 ? theTolerance : -theTolerance)
    {}

    // Compiler-generated copy ctor, copy op=, dctor are used

// ***** Tester: general public functions *****
public:

    // test
    // Handles single test, param indicates pass/fail
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (success)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    //  - Assuming exceptions have not been turned on for cout.
    void test(bool success,
              const std::string & testName = "")
    {
        ++countTests_;
        if (success) ++countPasses_;

        std::cout << "    ";
        if (testName != "")
        {
            std::cout << "Test: "
                      << testName
                      << " - ";
        }
        std::cout << (success ? "passed" : "********** FAILED **********")
                  << std::endl;
    }

    // ftest
    // Does single floating-point test.
    // Tests passes iff difference of first two values is <= tolerance.
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (abs(val1-val2) <= tolerance_)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    void ftest(double val1,
               double val2,
               const std::string & testName = "")
    { test(val1-val2 <= tolerance_ && val2-val1 <= tolerance_, testName); }

    // reset
    // Resets *this to default constructed state
    // Pre: None.
    // Post:
    //     countTests_ == 0, countPasses_ == 0
    // Does not throw (No-Throw Guarantee)
    void reset()
    {
        countTests_ = 0;
        countPasses_ = 0;
    }

    // numTests
    // Returns the number of tests that have been done since last reset 
    // Pre: None.
    // Post:
    //     return == countTests_
    // Does not throw (No-Throw Guarantee)
    int numTests() const
    { return countTests_; }

    // numPassed
    // Returns the number of tests that have passed since last reset
    // Pre: None.
    // Post:
    //     return == countPasses_
    // Does not throw (No-Throw Guarantee)
    int numPassed() const
    { return countPasses_; }

    // numFailed
    // Returns the number of tests that have not passed since last reset
    // Pre: None.
    // Post:
    //     return + countPasses_ == numTests_
    // Does not throw (No-Throw Guarantee)
    int numFailed() const
    { return countTests_ - countPasses_; }

    // allPassed
    // Returns true if all tests since last reset have passed
    // Pre: None.
    // Post:
    //     return == (countPasses_ == countTests_)
    // Does not throw (No-Throw Guarantee)
    bool allPassed() const
    { return countPasses_ == countTests_; }

    // setTolerance
    // Sets tolerance_ to given value
    // Pre: None.
    // Post:
    //     tolerance_ = abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    void setTolerance(double theTolerance)
    { tolerance_ = (theTolerance >= 0 ? theTolerance : -theTolerance); }

// ***** Tester: data members *****
private:

    int countTests_;    // Number of tests done since last reset
    int countPasses_;   // Number of tests passed since last reset
    double tolerance_;  // Tolerance for floating-point near-equality tests

};  // end class Tester


// ************************************************************************
// Testing Package:
//     Class TypeCheck - Helper Class for Type Checking
// ************************************************************************


// class TypeCheck
// This class exists in order to have static member function check, which
// takes a parameter of a given type, by reference. Objects of type
// TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//     returns true if the type of x is (MyType) or (const MyType),
//     otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // Uncopyable class. Do not define copy ctor, copy assn.
    TypeCheck(const TypeCheck &);
    TypeCheck<T> & operator=(const TypeCheck &);

    // Compiler-generated dctor is used (but irrelevant).

public:

    // check
    // The function and function template below simulate a single function
    // that takes a single parameter, and returns true iff the parameter has
    // type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check(const T & param)
    { return true; }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check(const OtherType & param)
    { return false; }

};  // End class TypeCheck


// ************************************************************************
// Testing Package:
//     Class Counter - Helper Class for Counting Calls & Objects, Throwing
// ************************************************************************


// class Counter
// Item type for counting ctor, dctor, op= calls, counting existing
//  objects, and possibly throwing on copy. Has operator< (which always
//  returns false), allowing it to be the value type of a sorted container.
// If static member copyThrow_ is set, then copy ctor and copy assn throw
//  std::runtime_error. Exception object's "what" member is set to "C" by
//  the copy ctor and "A" by copy assn.
// Increments static data member ctorCount_ on default construction and
//  successful copy construction. Increments static data member assnCount_
//  on successful copy assignment. Increments static data member
//  dctorCount_ on destruction.
// Increments static data member existing_ on construction, and decrements
//  it on destruction.
// Static data member maxExisting_ is highest value of existing_ since last
//  reset, or start of program if reset has never been called.
// Invariants:
//     Counter::existing_ is number of existing objects of this class.
//     Counter::ctorCount_ is number of successful ctor calls since
//      most recent call to reset, or start of program if reset has never
//      been called.
//     Counter::dctorCount_ is (similarly) number of dctor calls.
//     Counter::assnCount_ is (similarly) number of copy assn calls.
//     Counter::maxExisting_ is (similarly) highest value existing_ has
//      assumed.
class Counter {

// ***** Counter: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     (ctorCount_ has been incremented.)
    //     (existing_ has been incremented.)
    // Does not throw (No-Throw Guarantee)
    Counter()
    {
        ++existing_;
        if (existing_ > maxExisting_)
            maxExisting_ = existing_;
        ++ctorCount_;
    }

    // Copy ctor
    // Throws std::runtime_error if copyThrow_.
    // Pre: None.
    // Post:
    //     (ctorCount_ has been incremented.)
    //     (existing_ has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter(const Counter & other)
    {
        if (copyThrow_)
            throw std::runtime_error("C");
        ++existing_;
        if (existing_ > maxExisting_)
            maxExisting_ = existing_;
        ++ctorCount_;
    }

    // Copy assignment
    // Throws std::runtime_error if copyThrow_.
    // Pre: None.
    // Post:
    //     Return value is *this.
    //     (assnCount_ has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter & operator=(const Counter & rhs)
    {
        if (copyThrow_)
            throw std::runtime_error("A");
        ++assnCount_;
        return *this;
    }

    // Dctor
    // Pre: None.
    // Post:
    //     (dctorCount_ has been incremented.)
    //     (existing_ has been decremented.)
    // Does not throw (No-Throw Guarantee)
    ~Counter()
    {
        --existing_;
        ++dctorCount_;
    }

// ***** Counter: Functions dealing with count *****
public:

    // reset
    // Pre: None.
    // Post:
    //     maxExisting_ == existing_.
    //     ctorCount_ == 0.
    //     dctorCount_ == 0.
    //     assnCount_ == 0.
    //     copyThrow_ == shouldThrow.
    // Does not throw (No-Throw Guarantee)
    static void reset(bool shouldThrow = false)
    {
        maxExisting_ = existing_;
        ctorCount_ = 0;
        dctorCount_ = 0;
        assnCount_ = 0;
        copyThrow_ = shouldThrow;
    }

    // getExisting
    // Pre: None.
    // Post:
    //     return == existing_.
    // Does not throw (No-Throw Guarantee)
    static int getExisting()
    { return existing_; }

    // getMaxExisting
    // Pre: None.
    // Post:
    //     return == maxExisting_.
    // Does not throw (No-Throw Guarantee)
    static int getMaxExisting()
    { return maxExisting_; }

    // getCtorCount
    // Pre: None.
    // Post:
    //     return == ctorCount_.
    // Does not throw (No-Throw Guarantee)
    static int getCtorCount()
    { return ctorCount_; }

    // getDctorCount
    // Pre: None.
    // Post:
    //     return == dctorCount_.
    // Does not throw (No-Throw Guarantee)
    static int getDctorCount()
    { return dctorCount_; }

    // getAssnCount
    // Pre: None.
    // Post:
    //     return == assnCount_.
    // Does not throw (No-Throw Guarantee)
    static int getAssnCount()
    { return assnCount_; }

    // setCopyThrow
    // Pre: None.
    // Post:
    //     copyThrow_ == shouldThrow
    // Does not throw (No-Throw Guarantee)
    static void setCopyThrow(bool shouldThrow)
    { copyThrow_ = shouldThrow; }

// ***** Counter: Data Members *****
private:

    static int existing_;     // # of existing objects
    static int maxExisting_;  // Max # of existing objects
    static int ctorCount_;    // # of successful (non-throwing) ctor calls
    static int dctorCount_;   // # of dctor calls
    static int assnCount_;    // # of successful (non-throwing) copy = calls
    static bool copyThrow_;   // true if copy operations (ctor, =) throw

};  // End class Counter

// Definition of static data member of class Counter
int Counter::existing_ = 0;
int Counter::maxExisting_ = 0;
int Counter::ctorCount_ = 0;
int Counter::dctorCount_ = 0;
int Counter::assnCount_ = 0;
bool Counter::copyThrow_ = false;


// operator< (Counter)
// Dummy-ish operator<, forming a strict weak order for Counter class
// Returns false (which is legal for a strict weak order; all objects of
//  type Counter are equivalent).
// Pre: None.
// Post:
//     Return value == false.
// Does not throw (No-Throw Guarantee)
bool operator<(const Counter & a,
               const Counter & b)
{ return false; }


// ************************************************************************
// Test Suite Functions
// ************************************************************************


// test_class_Birthday_default_ctor
// Test suite for class Birthday, default ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class Birthday, default ctor" << std::endl;

    std::string s1;  // Holds names
    int i1;          // Holds months & days

    // Default construct const
    const Birthday con1;

    // Check default constructed const name
    s1 = con1.getName();
    t.test(s1 == "", "Default ctor, name");

    // Check default constructed const month
    i1 = con1.getMonth();
    t.test(i1 == 1, "Default ctor, month");

    // Check default constructed const day
    i1 = con1.getDay();
    t.test(i1 == 1, "Default ctor, day");
}


// test_class_Birthday_data_ctor
// Test suite for class Birthday, ctor from data
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_data_ctor(Tester & t)
{
    std::cout << "Test Suite: class Birthday, ctor from data" << std::endl;

    std::string s1;  // Holds names
    int i1;          // Holds months & days

    // data ctor param type
    const std::string s2("");
    Birthday con0(s2, 2, 2);  // This only needs to compile
    t.test(true, "Ctor from data, 1st param type = string");

    // Construct from data #1
    const Birthday con1("Fred X", 3, 7);

    // Check constructed from data #1 name
    s1 = con1.getName();
    t.test(s1 == "Fred X", "Ctor from data, non-const, name");

    // Check constructed from data #1 month
    i1 = con1.getMonth();
    t.test(i1 == 3, "Ctor from data, non-const, month");

    // Check constructed from data #1 day
    i1 = con1.getDay();
    t.test(i1 == 7, "Ctor from data, non-const, day");

    // Construct from data #2 (const)
    const Birthday con2("John Smith", 12, 31);

    // Check constructed from data #2 name
    s1 = con2.getName();
    t.test(s1 == "John Smith", "Ctor from data, const, name");

    // Check constructed from data #2 month
    i1 = con2.getMonth();
    t.test(i1 == 12, "Ctor from data, const, month");

    // Check constructed from data #2 day
    i1 = con2.getDay();
    t.test(i1 == 31, "Ctor from data, const, day");
}


// test_class_Birthday_get_and_set_functions
// Test suite for class Birthday, get & set functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_get_and_set_functions(Tester & t)
{
    std::cout << "Test Suite: class Birthday, get and set functions" << std::endl;

    std::string s1;  // Holds names
    int i1;          // Holds months & days

    bool typeCheck;  // For type checking functions
    std::string longString;
    for (int i = 0; i < 10000; ++i)
        longString += " abcd6789x";
    const std::string bigName = longString;  // "Name" of length 100,000

    Birthday con1("A", 2, 3);
    const Birthday & con1r(con1);
    Birthday con2("B", 9, 30);

    // setName parameter type
    Birthday con0;
    const std::string s2("");
    con0.setName(s2);  // This only needs to compile
    t.test(true, "setName param type = string");

    // Check getName return type non-const
    typeCheck = TypeCheck<std::string>::check(con1.getName());
    t.test(typeCheck, "getName non-const, return type = string");

    // Check getName return type const
    typeCheck = TypeCheck<std::string>::check(con1r.getName());
    t.test(typeCheck, "getName const, return type = string");

    // Check getMonth return type non-const
    typeCheck = TypeCheck<int>::check(con1.getMonth());
    t.test(typeCheck, "getMonth non-const, return type = int");

    // Check getMonth return type const
    typeCheck = TypeCheck<int>::check(con1r.getMonth());
    t.test(typeCheck, "getMonth const, return type = int");

    // Check getDay return type non-const
    typeCheck = TypeCheck<int>::check(con1.getDay());
    t.test(typeCheck, "getDay non-const, return type = int");

    // Check getDay return type const
    typeCheck = TypeCheck<int>::check(con1r.getDay());
    t.test(typeCheck, "getDay const, return type = int");

    // Check getName #1 non-const
    s1 = con1.getName();
    t.test(s1 == "A", "getName #1 non-const");

    // Check getName #1 const
    s1 = con1r.getName();
    t.test(s1 == "A", "getName #1 const");

    // Check getMonth #1 non-const
    i1 = con1.getMonth();
    t.test(i1 == 2, "getMonth #1 non-const");

    // Check getMonth #1 const
    i1 = con1r.getMonth();
    t.test(i1 == 2, "getMonth #1 const");

    // Check getDay #1 non-const
    i1 = con1.getDay();
    t.test(i1 == 3, "getDay #1 non-const");

    // Check getDay #1 const
    i1 = con1r.getDay();
    t.test(i1 == 3, "getDay #1 const");

    // Check getName #2
    s1 = con2.getName();
    t.test(s1 == "B", "getName #2");

    // Check getMonth #2
    i1 = con2.getMonth();
    t.test(i1 == 9, "getMonth #2");

    // Check getDay #2
    i1 = con2.getDay();
    t.test(i1 == 30, "getDay #2");

    // Check setName #1
    con1.setName("C");
    s1 = con1.getName();
    t.test(s1 == "C", "setName #1");

    // Check setMonth #1
    con1.setMonth(1);
    i1 = con1.getMonth();
    t.test(i1 == 1, "setMonth #1");

    // Check setDay #1
    con1.setDay(1);
    i1 = con1.getDay();
    t.test(i1 == 1, "setDay #1");

    // Check setName #2 big value
    con1.setName(bigName);
    s1 = con1.getName();
    t.test(s1 == bigName, "setName #2 big value");

    // Check setMonth #2 big value
    con1.setMonth(12);
    i1 = con1.getMonth();
    t.test(i1 == 12, "setMonth #2 big value");

    // Check setDay #2 big value
    con1.setDay(31);
    i1 = con1.getDay();
    t.test(i1 == 31, "setDay #2 big value");

    // Check getName #2
    s1 = con2.getName();
    t.test(s1 == "B", "getName #2 recheck");

    // Check getMonth #2
    i1 = con2.getMonth();
    t.test(i1 == 9, "getMonth #2 recheck");

    // Check getDay #2
    i1 = con2.getDay();
    t.test(i1 == 30, "getDay #2 recheck");
}


// test_class_Birthday_copy_ctor
// Test suite for class Birthday, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class Birthday, copy ctor" << std::endl;

    std::string s1;  // Holds names
    int i1;          // Holds months & days

    // Copy construct
    Birthday con1("Glenn G. Chappell", 2, 23);
    const Birthday & con1r(con1);
    Birthday con2(con1r);

    // Check copy name
    s1 = con2.getName();
    t.test(s1 == "Glenn G. Chappell", "Copy constructed, name");

    // Check copy month
    i1 = con2.getMonth();
    t.test(i1 == 2, "Copy constructed, Month");

    // Check copy day
    i1 = con2.getDay();
    t.test(i1 == 23, "Copy constructed, Day");

    // Modify original
    con1.setName("Pablo Picasso");
    con1.setMonth(10);
    con1.setDay(25);

    // Check original name
    s1 = con1.getName();
    t.test(s1 == "Pablo Picasso", "Original modified, original, name");

    // Check original month
    i1 = con1.getMonth();
    t.test(i1 == 10, "Original modified, original, month");

    // Check original day
    i1 = con1.getDay();
    t.test(i1 == 25, "Original modified, original, day");

    // Check copy name
    s1 = con2.getName();
    t.test(s1 == "Glenn G. Chappell", "Original modified, copy constructed, name");

    // Check copy month
    i1 = con2.getMonth();
    t.test(i1 == 2, "Original modified, copy constructed, month");

    // Check copy day
    i1 = con2.getDay();
    t.test(i1 == 23, "Original modified, copy constructed, day");

    // Modify copy
    con2.setName("Albert Einstein");
    con2.setMonth(3);
    con2.setDay(14);

    // Check original name
    s1 = con1.getName();
    t.test(s1 == "Pablo Picasso", "Copy modified, original, name");

    // Check original month
    i1 = con1.getMonth();
    t.test(i1 == 10, "Copy modified, original, month");

    // Check original day
    i1 = con1.getDay();
    t.test(i1 == 25, "Copy modified, original, day");

    // Check copy name
    s1 = con2.getName();
    t.test(s1 == "Albert Einstein", "Copy modified, copy constructed, name");

    // Check copy month
    i1 = con2.getMonth();
    t.test(i1 == 3, "Copy modified, copy constructed, month");

    // Check copy day
    i1 = con2.getDay();
    t.test(i1 == 14, "Copy modified, copy constructed, day");
}


// test_class_Birthday_copy_assn
// Test suite for class Birthday, copy assignment
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class Birthday, copy assignment" << std::endl;

    std::string s1;  // Holds names
    int i1;          // Holds months & days

    // Copy construct
    Birthday con1("Glenn G. Chappell", 2, 23);
    const Birthday & con1r(con1);
    Birthday con2;
    con2 = con1r;

    // Check copy name
    s1 = con2.getName();
    t.test(s1 == "Glenn G. Chappell", "Copy constructed, name");

    // Check copy month
    i1 = con2.getMonth();
    t.test(i1 == 2, "Copy constructed, Month");

    // Check copy day
    i1 = con2.getDay();
    t.test(i1 == 23, "Copy constructed, Day");

    // Modify original
    con1.setName("Pablo Picasso");
    con1.setMonth(10);
    con1.setDay(25);

    // Check original name
    s1 = con1.getName();
    t.test(s1 == "Pablo Picasso", "Original modified, original, name");

    // Check original month
    i1 = con1.getMonth();
    t.test(i1 == 10, "Original modified, original, month");

    // Check original day
    i1 = con1.getDay();
    t.test(i1 == 25, "Original modified, original, day");

    // Check copy name
    s1 = con2.getName();
    t.test(s1 == "Glenn G. Chappell", "Original modified, copy constructed, name");

    // Check copy month
    i1 = con2.getMonth();
    t.test(i1 == 2, "Original modified, copy constructed, month");

    // Check copy day
    i1 = con2.getDay();
    t.test(i1 == 23, "Original modified, copy constructed, day");

    // Modify copy
    con2.setName("Albert Einstein");
    con2.setMonth(3);
    con2.setDay(14);

    // Check original name
    s1 = con1.getName();
    t.test(s1 == "Pablo Picasso", "Copy modified, original, name");

    // Check original month
    i1 = con1.getMonth();
    t.test(i1 == 10, "Copy modified, original, month");

    // Check original day
    i1 = con1.getDay();
    t.test(i1 == 25, "Copy modified, original, day");

    // Check copy name
    s1 = con2.getName();
    t.test(s1 == "Albert Einstein", "Copy modified, copy constructed, name");

    // Check copy month
    i1 = con2.getMonth();
    t.test(i1 == 3, "Copy modified, copy constructed, month");

    // Check copy day
    i1 = con2.getDay();
    t.test(i1 == 14, "Copy modified, copy constructed, day");
}


// test_class_Birthday_toString
// Test suite for class Birthday, toString
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_toString(Tester & t)
{
    std::cout << "Test Suite: class Birthday, toString" << std::endl;

    std::string s1;  // Holds output

    bool typeCheck;  // For type checking functions
    std::string longString;
    for (int i = 0; i < 10000; ++i)
        longString += " abcd6789x";
    const std::string bigName = longString;  // "Name" of length 100,000

    // Test #1
    Birthday con1("Glenn G. Chappell", 2, 23);

    // Check toString non-const return type
    typeCheck = TypeCheck<std::string>::check(con1.toString());
    t.test(typeCheck, "toString non-const, return type = string");

    // Check toString #1
    s1 = con1.toString();
    t.test(s1 == "Glenn G. Chappell (Feb 23)", "toString non-const, value");

    // Test #2 (const)
    const Birthday con2(" Bill Bill ", 3, 4);

    // Check toString onst return type
    typeCheck = TypeCheck<std::string>::check(con2.toString());
    t.test(typeCheck, "toString const, return type = string");

    // Check toString #2
    s1 = con2.toString();
    t.test(s1 == " Bill Bill  (Mar 4)", "toString const, value");

    // Test #3 (default constructed)
    Birthday con3;
    
    // Check toString #3
    s1 = con3.toString();
    t.test(s1 == " (Jan 1)", "toString default constructed, value");

    // Check toString big value
    s1 = Birthday(bigName, 12, 31).toString();
    t.test(s1 == bigName + " (Dec 31)", "toString big value");
}


// test_class_Birthday_stream_insertion
// Test suite for class Birthday, stream insertion
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_stream_insertion(Tester & t)
{
    std::cout << "Test Suite: class Birthday, stream insertion" << std::endl;

    std::string s1;  // Holds output

    std::string longString;
    for (int i = 0; i < 10000; ++i)
        longString += " abcd6789x";
    const std::string bigName = longString;  // "Name" of length 100,000

    // Test #1
    Birthday con1("Glenn G. Chappell", 2, 23);

    // Check stream insertion #1
    std::ostringstream oss1a;
    oss1a << con1;
    s1 = oss1a.str();
    t.test(s1 == "Glenn G. Chappell (Feb 23)", "Stream insertion non-const");

    // Check stream insertion #1 + added text
    std::ostringstream oss1b;
    oss1b << "x" << con1 << "y";
    s1 = oss1b.str();
    t.test(s1 == "xGlenn G. Chappell (Feb 23)y", "Stream insertion non-const, with added text");

    // Test #2 (const)
    const Birthday con2(" Bill Bill ", 3, 4);
    // Check stream insertion #2
    std::ostringstream oss2a;
    oss2a << con2;
    s1 = oss2a.str();
    t.test(s1 == " Bill Bill  (Mar 4)", "Stream insertion const");

    // Check stream insertion #2 + added text
    std::ostringstream oss2b;
    oss2b << "x" << con2 << "y";
    s1 = oss2b.str();
    t.test(s1 == "x Bill Bill  (Mar 4)y", "Stream insertion const, with added text");

    // Test #3 (default constructed)
    Birthday con3;

    // Check stream insertion #3
    std::ostringstream oss3a;
    oss3a << con3;
    s1 = oss3a.str();
    t.test(s1 == " (Jan 1)", "Stream insertion default constructed");

    // Check stream insertion #3
    std::ostringstream oss3b;
    oss3b << "x" << con3 << "y";
    s1 = oss3b.str();
    t.test(s1 == "x (Jan 1)y", "Stream insertion default constructed, with added text");

    // Check stream insertion big value
    s1 = Birthday(bigName, 12, 31).toString();
    t.test(s1 == bigName + " (Dec 31)", "stream insertion big value");
}


// test_class_Birthday_comparisons
// Test suite for class Birthday, comparisons
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday_comparisons(Tester & t)
{
    std::cout << "Test Suite: class Birthday, comparisons" << std::endl;

    const Birthday con1("Glenn G. Chappell", 2, 23);
    const Birthday con2("Bill Bill", 3, 4);
    Birthday con1copy1(con1);
    Birthday con1copy2(con1);
    Birthday con1copy3(con1);

    // Check equality of copies
    t.test(con1 == con1copy1, "Equality of copies");

    // Check inequality of copies
    t.test(!(con1 != con1copy1), "Inequality of copies");

    // Check equality of different names
    // (Also checks param types)
    t.test(!(con1 == con2), "Equality of different Birthdays");

    // Check inequality of different names
    // (Also checks param types)
    t.test(con1 != con2, "Inequality of different Birthdays");

    // Modify copy #1
    con1copy1.setName("Pablo Picasso");

    // Check equality of modification of copy (name)
    t.test(!(con1 == con1copy1),
          "Equality of modification of copy (name)");

    // Check inequality of modification of copy (name)
    t.test(con1 != con1copy1,
          "Inquality of modification of copy (name)");

    // Modify copy #2
    con1copy2.setMonth(10);

    // Check equality of modification of copy (month)
    t.test(!(con1 == con1copy2),
          "Equality of modification of copy (month)");

    // Check inequality of modification of copy (month)
    t.test(con1 != con1copy2,
          "Inequality of modification of copy (month)");

    // Modify copy #3
    con1copy3.setDay(25);

    // Check equality of modification of copy (day)
    t.test(!(con1 == con1copy2),
          "Equality of modification of copy (day)");

    // Check inequality of modification of copy (day)
    t.test(con1 != con1copy2,
          "Inequality of modification of copy (day)");

    // Create separately set equal values
    con1copy1.setName("Bill Bill");
    con1copy1.setMonth(3);
    con1copy1.setDay(4);

    // Check equality of separately set equal values
    t.test(con1copy1 == con2,
          "Equality of separately set equal values");

    // Check inequality of separately set equal values
    t.test(!(con1copy1 != con2),
          "Equality of separately set equal values");
}


// test_class_Birthday
// Test suite for class Birthday
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_Birthday(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS Birthday" << std::endl;
    test_class_Birthday_default_ctor(t);
    test_class_Birthday_data_ctor(t);
    test_class_Birthday_get_and_set_functions(t);
    test_class_Birthday_copy_ctor(t);
    test_class_Birthday_copy_assn(t);
    test_class_Birthday_toString(t);
    test_class_Birthday_stream_insertion(t);
    test_class_Birthday_comparisons(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class Birthday test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_Birthday(t);

    std::cout << std::endl;
    if (t.allPassed())
    {
        std::cout << "All tests successful" 
                  << std::endl;
    }
    else
    {
        std::cout << "Tests ********** UNSUCCESSFUL **********"
                  << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Press ENTER to quit ";
    while (std::cin.get() != '\n') ;

    return 0;
}

