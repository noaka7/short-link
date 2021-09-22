CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall -O2
LDFLAGS=-lrt -lm

INC=include

objects=short_link tests

all: $(objects)

short_link: short_link.cpp
	$(CXX) $(CXXFLAGS) -I$(INC) -c -o $@ $<

tests: tests.cpp short_link.cpp
	$(CXX) $(CXXFLAGS) -I$(INC) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	-rm $(objects)
