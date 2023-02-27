/*
 * CSC-301
 * project1.hpp
 * Fall 2022
 *
 * Author: Shrey Agrawal
 * Date: Due 02/20/23
 * 
 */

#ifndef PROJECT1_HPP_
#define PROJECT1_HPP_

#include <iostream>
#include <vector>

void selectionSort(std::vector<double> &arrayToSort);
void insertionSort(std::vector<double> &arrayToSort);
void bubbleSort(std::vector<double> &arrayToSort);
void mergeSort(std::vector<double> &arrayToSort);
void mergeSortHelper(std::vector<double> &arrayToSort, std::vector<double> &left, std::vector<double> &right);
void quickSortHelper(std::vector<double> &arrayToSort, int i, int j);
void quickSort(std::vector<double> &arrayToSort);

#endif  // PROJECT1_HPP_