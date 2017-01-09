OBJS = ExponentialRV.o
CC = g++
DEBUG = -g
CXXFLAGS = -Wall -c -std=c++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: Exponential

Exponential : ExponentialRV.o
	$(CC) $(LFLAGS) testExponentialRV.cpp ExponentialRV.o -o Exponential

ExponentialRV.o : ExponentialRV.hpp RandomVariable.hpp
	$(CC) $(CXXFLAGS) ExponentialRV.cpp

clean: 
	\rm -f *.o *~ Exponential

tar:
	tar cfv RVLib.tar RandomVariable.hpp ExponentialRV.hpp ExponentialRV.cpp \
		testExponentialRV.cpp
