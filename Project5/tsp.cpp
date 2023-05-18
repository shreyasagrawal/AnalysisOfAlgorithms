/*
 * CSC-301
 * tsp.cpp
 * Spring 2023
 *
 * Shrey Agrawal
 * Due Date: 05/05/2023
 */

#include "tsp.hpp"

using namespace std;

/*
 * tsp
 * Returns the tour of the graph.
 * @param adjList: the adjacency list
 * @param start: the start vertex
 * @return: the tour of the graph
 */
vector<int> tsp(vector<Vertex> &adjList, Vertex &start) {
    // Create the empty tour.
    vector<int> tour;
    
    // Create the vector for tracking visited during the DFS.
    int n = adjList.size();
    vector<bool> visited(n, false);

    // Create a stack for DFS traversal.
    stack<int> dfsStack;
    // Push the start vertex onto the stack.
    dfsStack.push(start.label);

    // Visit vertices using DFS.
    while (!dfsStack.empty()) {
        // Get current vertex.
        int currentVertex = dfsStack.top();
        // Remove current vertex from stack.
        dfsStack.pop();


        // Add current vertex to tour if not visited.
        if (!visited[currentVertex]) {
            tour.push_back(currentVertex);
            visited[currentVertex] = true;
        }

        // Add unvisited MST neighbors to stack.
        for (int neighbor : adjList[currentVertex].mstNeighbors) {
            if (!visited[neighbor]) {
                dfsStack.push(neighbor);
            }
        }
    }

    // Complete cycle by returning to start vertex.
    tour.push_back(start.label);



    return tour;
}