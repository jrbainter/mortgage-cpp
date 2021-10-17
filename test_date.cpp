// test_date.cpp

#include <iostream>
#include <string>
#include <array>
#include "date.h"

using namespace std;


int main() {

	// Test data

	array<string,9> test_data {"1/2/1996", "11/15/2001", "2/6/2015",
							   "12/6/2019", "2/5/19569","30/22/1900",
							   "1/5/3000", "12/32/2017", "22/6/2015" };

	for(auto ds:test_data)
	{
		Date* d = new Date(ds);
		string s = d->get();
		if (d->verify(s))
			cout << s << " Date is valid\n";			
		else {
			cout << s << " BAD Date\n";
			continue;
		}
		d->add_month();
		s = d->get();
		cout << "Next Month : " << s << endl;
		
		delete d;
	}
		
	Date* d = new Date("2/20/2015");
	for(int i=0; i<30; ++i) {
		cout << d->get();
		(i % 6) ? cout << " " : cout << endl;
		d->add_month();
	}
	cout << endl;
	delete d;
}
