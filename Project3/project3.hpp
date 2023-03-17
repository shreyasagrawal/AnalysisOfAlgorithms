/*
 * CSC-301
 * project3.hpp
 * Spring 2023
 * Shrey Agrawal
 * Due Date: 03.17.2023
 */

#ifndef PROJECT3_HPP_
#define PROJECT3_HPP_

#include <iostream>
#include <vector>
#include <math.h>

/*
 * createAdjacencyMatrix
 */
std::vector<double> createAdjacencyMatrix(std::vector<double> &rates,
                                          std::vector<std::string> &currencies);

/*
 * detectArbitrage
 */
std::vector<int> detectArbitrage(std::vector<double> &adjMatrix,
                                 std::vector<std::string> &currencies,
                                 double tol=1e-15);

#endif  // PROJECT3_HPP_