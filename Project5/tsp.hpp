/*
 * CSC-301
 * tsp.hpp
 * Spring 2023
 *
 * Shrey Agrawal
 * Due Date: 05/05/2023
 */

#ifndef TSP_HPP_
#define TSP_HPP_

#include <stack>

#include "Vertex.hpp"

/*
 * tsp
 */
std::vector<int> tsp(std::vector<Vertex> &adjList, Vertex &start);

#endif  // TSP_HPP_