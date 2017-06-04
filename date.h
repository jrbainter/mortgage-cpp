// date.h

#ifndef MORT_DATE_H
#define MORT_DATE_H
#include <string>

using namespace std;

class Date {
	
	public:
	Date(int, int, int, char);
	Date(string);
	~Date();
	string get();
	string to_string();
	void add_month();
	bool verify(const string&);
	
	private:
	int year;
	int month;
	int day;
	string sdate;
	char sepchar;

};
		
#endif // MORT_DATE_H
