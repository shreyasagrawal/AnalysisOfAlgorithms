/*
 * CSC-301
 * project4.hpp
 * Spring 2023
 *
 * Shrey Agrawal
 * Date: Due 04/17/2023
 */

#ifndef PROJECT4_HPP_
#define PROJECT4_HPP_

#include <iostream>
#include <vector>
#include "Edit.hpp"

/*
 * ED
 */
std::vector<int> ED(std::string &src, std::string &dest, bool useASM);

/*
 * getNumEdits
 */
int getNumEdits(std::string &src, std::string &dest, std::vector<int> &table);

/*
 * getEdits
 */
std::vector<Edit> getEdits(std::string &src, std::string &dest, 
                           std::vector<int> &table);

/*
 * printTable: prints the table so it looks nice.
 *
 * INPUTS
 * string src: the source string for ED (or ASM).
 * string dest: the destination string for ED (or ASM).
 * vector<int> &table: the table itself.
 *
 * OUTPUTS
 * string tableString.str(): the pretty string.
 */
std::string printTable(std::string &src, std::string &dest, 
                       std::vector<int> &table);

#endif  // PROJECT4_HPP_