all : Lab3

CXX = g++ -std=c++11
LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3


Lab3: Lab3.o graph.o
	$(CXX) $(LINKFLAGS) Lab3.o graph.o -o Lab3

Lab3.o : Lab3.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"'date'\"" Lab3.cpp -c
 
graph.o : graph.cpp graph.h block.h terminal.h
	$(CXX) $(LINKFLAGS) graph.cpp -c 
 
clean:
	rm -rf *.o *.gch Lab3

