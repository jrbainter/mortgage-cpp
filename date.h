// date.h

#ifndef MORT_DATE_H
#define MORT_DATE_H
#include <string>

using namespace std;

class Date {
	
private:
	int year, month,day;
	string sdate;
	char sepchar;
	
public:
	Date(int, int, int, char);
	Date(string);
	~Date();
	string get();
	string to_string();
	void add_month();
	bool verify(const string&);
	

};
		
#endif // MORT_DATE_H
