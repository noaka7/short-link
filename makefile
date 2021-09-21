CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall -O2
LDFLAGS=-lrt -lm

objects=short_link tests

all: $(objects)

short_link: short_link.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests: tests.cpp short_link.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	-rm $(objects)
