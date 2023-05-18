/*
 * CSC-301
 * Vertex.cpp
 * Fall 2022
 * Eric A. Autry
 * 09/23/22
 */

#include "Vertex.hpp"

using namespace std;

/*
 * Constructor for the Vertex class.
 * 
 * Sets the label to be the input label.
 * Defaults visited to false and previous to -1.
 * Note that neighbors defaults as an empty vector automatically.
 */
Vertex::Vertex(int labelSet) {
    label = labelSet;
    visited = false;
    previous = -1;
}

/*
 * printVertex creates a string that nicely prints info about the Vertex.
 */
string Vertex::printVertex() {
    stringstream toPrint;
    toPrint << "Label: " << to_string(label);
    toPrint << endl;
    if (visited) {
        toPrint << "Visited" << endl;
    } else {
        toPrint << "Not Visited" << endl;
    }
    toPrint << "Previous Vertex: " << to_string(previous) << endl;
    toPrint << "Neighbors:" << endl;
    for (int neigh : neighbors) {
        toPrint << to_string(neigh) << " ";
    }
    toPrint << endl;
    return toPrint.str();
}