/*
 * CSC-301
 * maze.hpp
 * Fall 2022
 * Eric A. Autry
 * 09/23/22
 */

#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <sstream>
#include <math.h>
#include "project2.hpp"

std::vector<int> createMaze(int mazeNum, int numChambers);
std::pair<int,int> findStartExit(std::vector<int> &maze);
std::string printRoomNums(std::vector<int> &maze);
std::vector<Vertex> makeAdjList(std::vector<int> &maze);
bool checkMaze(std::vector<int> &maze, std::vector<int> &path, bool verb);
std::string printMaze(std::vector<int> &maze, std::vector<int> &path);
std::pair<bool,bool> testMaze(int mazeNum, bool verb);
int main(int argc, char* argv[]);

#endif  // MAZE_HPP_