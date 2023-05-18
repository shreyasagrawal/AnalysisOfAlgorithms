/*
 * CSC-301
 * kruskal.cpp
 * Spring 2023
 *
 * Shrey Agrawal
 * Due Date: 05/05/2023
 */

#include "kruskal.hpp"

using namespace std;

/*
 * find
 * Returns the representative of the set containing v.
 * @param v: the vertex
 * @param pi: the pi vector
 * @return: the representative of the set containing v
 * 
 */

int find(int v, vector<int> &pi) {
    // If v is not the representative of its set, updating its pi pointer.
    if (pi[v] != v) {
        pi[v] = find(pi[v], pi);
    }
    return pi[v];
}

/*
 * union_by_rank
 * Unions the sets containing u and v.
 * @param u: the first vertex
 * @param v: the second vertex
 * @param rank: the rank vector
 * @param pi: the pi vector
 * 
 */
void union_by_rank(int u, int v, vector<int> &rank, vector<int> &pi) {
    // Finding the representatives of the sets containing u and v.
    u = find(u, pi);
    v = find(v, pi);
    // If u and v are in the same set, returning.
    if (rank[u] > rank[v]) {
        pi[v] = u;
    } else {
        // Otherwise, updating the pi pointer of the representative of the
        // smaller set to be the representative of the larger set.
        pi[u] = v;
        if (rank[u] == rank[v]) {
            rank[v]++;
        }
    }
}

/*
 * kruskal
 * Returns the MST of the graph.
 * @param adjList: the adjacency list
 * @param edgeList: the edge list
 * @return: the MST of the graph
 */
vector<Edge> kruskal(vector<Vertex> &adjList, vector<Edge> &edgeList) {
    // Initialize the empty MST.
    vector<Edge> mst;
    
    // For each vertex, we need rank values and pi pointers (ints) for the
    // Disjoint Sets. Initialize the rank to 0 and pi to be the vertex labels.
    int n = adjList.size();
    vector<int> rank(n, 0);
    vector<int> pi(n);
    for (int i=0; i<pi.size(); i++) {
        pi[i] = i;
    }

    // Iterate through the edges in edgeList, adding each edge to the MST if it
    // does not create a cycle.
    for (Edge edge : edgeList) {
        int u = edge.first.label;
        int v = edge.second.label;
        // If u and v are not in the same set, adding the edge to the MST and
        // unioning the sets containing u and v.
        if (find(u, pi) != find(v, pi)) {
            mst.push_back(edge);
            union_by_rank(u, v, rank, pi);
        }
    }

    // Update the mstNeighbors of each vertex based on the edges in the MST.
    for (Edge edge : mst) {
        int u = edge.first.label;
        int v = edge.second.label;
        // Adding v to the mstNeighbors of u and u to the mstNeighbors of v.
        adjList[u].mstNeighbors.push_back(v);
        adjList[v].mstNeighbors.push_back(u);
    }

    return mst;
}