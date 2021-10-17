objects = date.o test_date.o
flags = -std=c++14
OBJS = mortgage.o date.o
CXX = $(shell fltk-config --cxx)
LINK = $(CXX)
LDFLAGS = $(shell fltk-config --ldflags)
LDSTATIC = $(shell fltk-config --ldstaticflags )

mortgage : $(OBJS)
	g++ -o mortgage $(OBJS) $(LDFLAGS)

test_date : date.o test_date.o
	g++  $(flags) $(objects) -o test_date

mortgage.o : mortgage.cxx date.cpp date.h
	$(CXX) $(flags) $(fltk-config --cflags) -c mortgage.cxx
	
date.o : date.cpp date.h
	g++ $(flags) -c date.cpp
	
test_date.o : test_date.cpp date.cpp date.h
	g++ $(flags) -c test_date.cpp

clean :
	rm *.o
