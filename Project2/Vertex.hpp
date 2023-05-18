/*
 * CSC-301
 * Vertex.hpp
 * Fall 2022
 * Eric A. Autry
 * 09/23/22
 */

#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>

/*
 * Vertex Class for the mazes.
 */
class Vertex {

    public:
        explicit Vertex(int labelSet);

        int label;                  // The label for this vertex as an int.
        std::vector<int> neighbors; // The list of labels of the neighbors.
        bool visited;               // The visited flag.
        int previous;               // The previous vertex on the path.

        // Overloaded == compares two Vertex objects based on their labels.
        bool operator == (Vertex const &other) const {
            return label == other.label;
        }

        // printVertex returns a string clearly printing info about the Vertex.
        std::string printVertex();
};

#endif  // VERTEX_HPP_