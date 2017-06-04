// date.cpp

#include <string>
#include <sstream>
#include <regex>
#include "date.h"


using namespace std;

	
	string Date::to_string() {
		ostringstream os;
		os << month << sepchar << day << sepchar << year;
		return os.str();
	}	
	


	Date::Date(const int mm, const int dd, const int yy, char sep = '/')
		: month{mm}, day{dd}, year{yy}, sepchar{sep} {
		// convert ints month, day and year to string "sDate::Date"
		sdate = to_string();
	}
	
	Date::Date(string s) : sdate{s} {
		// date string: mm/dd/yyyy
		// separate the date string into its
		// month, day, and year elements

		istringstream convert{s};
		convert >> month >> sepchar >> day >> sepchar >> year;
		// Keep day number simple (no leap year)
		if (day > 28) day = 28;

	}

	Date::~Date(){};
	
	string Date::get() {return sdate;}
	
	void Date::add_month() {
		 month += 1;
		if (month == 13) {
			month = 1;
			year += 1;
		}
		// rebuild string "sdate"
		sdate = to_string();
	}


	
	bool Date::verify(const string& s) {
		// verify date formated correctly
		// "m|mm/d|dd/yy|yyyy"
		regex pat {R"((^0?[1-9]|1[012])[- /.](0?[1-9]|[12][0-9]|3[01])[- /.](19|20)\d\d$)"};
		return regex_match(s, pat);
	}
		

