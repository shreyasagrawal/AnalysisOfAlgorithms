/*
 * CSC-301
 * prim.cpp
 * Spring 2023
 *
 * Shrey Agrawal
 * Due Date: 05/05/2023
 */

#include "prim.hpp"

using namespace std;

/*
 * getMin
 * Returns the vertex with the minimum cost.
 * @param cost: the cost vector
 * @param visited: the visited vector
 * @return: the vertex with the minimum cost
 *         -1 if all vertices have been visited
 */
int getMin(vector<double> &cost, vector<bool> &visited) {
    // Initializing the minimum vertex and cost.
    int minVertex = -1;
    double minCost = numeric_limits<double>::infinity();

    // Looping through the cost vector, updating the minimum vertex and cost.
    for (int i = 0; i < cost.size(); i++) {
        if (!visited[i] && cost[i] < minCost) {
            minVertex = i;
            minCost = cost[i];
        }
    }
    return minVertex;
}

/*
 * isEmpty
 * Returns true if all vertices have been visited.
 * @param visited: the visited vector
 * @return: true if all vertices have been visited
 *         false otherwise
 */
bool isEmpty(vector<bool> &visited) {
    // Looping through the visited vector, returning false if any vertex is not
    for (bool v : visited) {
        if (!v) {
            return false;
        }
    }
    return true;
}

/*
 * prim
 * Returns the MST of the graph.
 * @param adjList: the adjacency list
 * @param adjMat: the adjacency matrix
 * @return: the MST of the graph
 *        (should never be empty)
 * 
 */
vector<Edge> prim(vector<Vertex> &adjList, vector<double> &adjMat) {
    // Initialize the empty MST.
    vector<Edge> mst;
    
    // For each vertex, we need a visited flag, a 'cost' for Prim's, and the
    // prev values to track the MST. Store these in seperate vectors.
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<double> cost(n, numeric_limits<double>::infinity());
    vector<int> prev(n, -1);

    // Start with the first vertex.
    int currVertex = 0;
    cost[currVertex] = 0;

    // Loop until all vertices have been visited.
    while (!isEmpty(visited)) {
        visited[currVertex] = true;

        // Update the cost and prev values for each neighbor.
        for (int neighbor : adjList[currVertex].neighbors) {
            // If the neighbor has not been visited and the cost is less than
            // the current cost, update the cost and prev values.
            if (!visited[neighbor] && adjMat[currVertex * n + neighbor] < cost[neighbor]) {
                cost[neighbor] = adjMat[currVertex * n + neighbor];
                prev[neighbor] = currVertex;
            }
        }

        // Find the minimum cost vertex.
        currVertex = getMin(cost, visited);
        if (currVertex == -1) {
            break; // All vertices have been visited.
        }

        // Add the corresponding edge to the MST.
        int prevVertex = prev[currVertex];
        // If the previous vertex is not -1, add the edge to the MST.
        if (prevVertex != -1) {
            mst.push_back(Edge(adjList[prevVertex], adjList[currVertex], adjMat[prevVertex * n + currVertex]));
            adjList[prevVertex].mstNeighbors.push_back(currVertex);
            adjList[currVertex].mstNeighbors.push_back(prevVertex);
        }
    }

    return mst;
}