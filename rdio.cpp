// test redirect to cout io to a file

#include <iostream>
#include <fstream>

using namespace std;


int main()
{
	cout << "Write to stdout" << endl;
	filebuf buf;
	
	buf.open("testio.txt", ios::out);
	auto oldbuf = cout.rdbuf(&buf);
	
	cout << "Write to file..." << endl;
	cout.rdbuf(oldbuf);
	
	cout << "write to stdout" << endl;
	
}	
