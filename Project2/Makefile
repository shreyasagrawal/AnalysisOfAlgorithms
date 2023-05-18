# Makefile for CSC-301 Project #1
# Eric A. Autry, 09/08/22
# 
# As usual, you can build this software by typing:
#
#     make


# ----- Make Macros -----

CXXFLAGS =	-O3
CXX	=	clang

TARGETS =	maze
OBJECTS =	maze.cpp project2.cpp Vertex.cpp
REMOVE =	maze.o project2.o Vertex.o
LINKS =	-std=c++20 -lstdc++ -lm
INCLUDE = 

# ----- Make Rules -----

all:	$(TARGETS)

maze:	$(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o maze $(OBJECTS) $(LINKS)

clean:
	rm -f $(TARGETS) $(REMOVE)