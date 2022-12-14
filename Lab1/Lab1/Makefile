all : Lab1

CXX = g++
LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3
HEADERS = graph.h tile.h 
SOURCES = graph.cpp Lab1.cpp
OBJECTS = graph.o Lab1.o


Lab1: Lab1.o graph.o
	$(CXX) $(LINKFLAGS) Lab1.o graph.o -o Lab1

Lab1.o : Lab1.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"'date'\"" Lab1.cpp -c
 
graph.o : graph.cpp graph.h tile.h
	$(CXX) $(LINKFLAGS) graph.cpp -c 
 
clean:
	rm -rf *.o *.gch Lab1

