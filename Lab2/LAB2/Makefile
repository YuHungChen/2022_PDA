all : Lab2

CXX = g++
LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3
HEADERS = B_tree.h Treenode.h
SOURCES = Lab2.cpp B_tree.cpp
OBJECTS = Lab2.o B_tree.o


Lab2: Lab2.o B_tree.o
	$(CXX) $(LINKFLAGS) Lab2.o B_tree.o -o Lab2

Lab2.o : Lab2.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"'date'\"" Lab2.cpp -c
 
B_tree.o : B_tree.cpp B_tree.h Treenode.h contour.h terminal.h
	$(CXX) $(LINKFLAGS) B_tree.cpp -c 
 
clean:
	rm -rf *.o *.gch Lab2

