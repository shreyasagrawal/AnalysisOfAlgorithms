/*
 * CSC-301
 * project2.cpp
 * Spring 2023
 *
 * Shrey Agrawal
 * Due Date: March 9 2023
 */

#include "project2.hpp"

using namespace std;

/*
 * Depth First Search
 * The input of this function is an adjacency list representation of a graph
 * The start and exxit variable is from the class Vertex representing the start and end of a maze
 * The output is a path that is followed from start to end to solve the maze in a DFS manner
 */
vector<int> DFS(vector<Vertex> &adjList, Vertex &start, Vertex &exit) {
    vector<int> path;
    stack<int> intstack;

    // initializing all the verticies in the maze by pointing the previous to be -1 and visited to be false
    for (int i = 0; i<adjList.size(); i++)
        {
            adjList[i].previous = -1;
            adjList[i].visited = false;
        }
    
    start.visited = true;
    intstack.push(start.label);

    while (!intstack.empty()){
        //pop the top element off the stack and making it the current element
        int curr = intstack.top();
        intstack.pop();

        // we need to check if the vertex we just popped off is the final exit vertex
        if (curr == exit.label){
        //we're done, but we need to get the path and update the path variable
        // since path is a vector and c++ has nice methods, the process of tracing is simplified

            //repeat pushing the vertex label onto the path until the start is found
            while (curr != start.label){
                //this adds the label of the last vertex into the path variable
                path.push_back(curr);
                curr = adjList[curr].previous;
            }
            //adding the start vertex
            path.push_back(start.label);
            //this allows to convert our path that is from exit to start to be from start to exit
            reverse(path.begin(), path.end());

            break;

        }

        for (int j = 0; j<adjList[curr].neighbors.size(); j++){
            // choosing a neighbor of the current vertex
            int neighbor = adjList[curr].neighbors[j];
            
            // if this neighbor is not visited, we visit it, and push it onto the stack

            if(!adjList[neighbor].visited){
                //changing the status of the vertex to be visited since we are going to push it onto the stack
                adjList[neighbor].visited = true;
                intstack.push(adjList[neighbor].label);

                // we also want to keep track of the path from the start vertex 
                // to the current vertex. This is so that we can trace the path 
                //from the start vertex to the exit vertex once we reach it.
                adjList[neighbor].previous = curr;

            }

        }
    }

    return path;
}

/*
 * Breadth First Search
 * The input of this function is an adjacency list representation of a graph
 * The start and exit variable is from the class Vertex representing the start and end of a maze
 * The output is a path that is followed from start to end to solve the maze in a BFS manner
 * main difference between this and DFS is DFS uses a stack, BFS uses a queue
 */
vector<int> BFS(vector<Vertex> &adjList, Vertex &start, Vertex &exit) {
    vector<int> path;
    queue<int> intq;

    // initializing all the verticies in the maze by pointing the previous to be -1 and visited to be false
    for (int i = 0; i<adjList.size(); i++)
        {
            adjList[i].previous = -1;
            adjList[i].visited = false;
        }
    
    start.visited = true;
    intq.push(start.label);

    while (!intq.empty()){
        //pop the front element off the queue and making it the current element
        int curr = intq.front();
        intq.pop();

        // we need to check if the vertex we just popped off is the final exit vertex
        if (curr == exit.label){
        // we're done, but we need to get the path and update the path variable
        // since path is a vector and c++ has nice methods, the process of tracing is simplified

            //repeat pushing the vertex label onto the path until the start is found
            while (curr != start.label){
                //this adds the label of the last vertex into the path variable
                path.push_back(curr);
                curr = adjList[curr].previous;
            }
            //adding the start vertex
            path.push_back(start.label);
            //this allows to convert our path that is from exit to start to be from start to exit
            reverse(path.begin(), path.end());

            break;

        }

        for (int j = 0; j<adjList[curr].neighbors.size(); j++){
            // choosing a neighbor of the current vertex
            int neighbor = adjList[curr].neighbors[j];
            
            // if this neighbor is not visited, we visit it, and push it onto the queue

            if(!adjList[neighbor].visited){
                //changing the status of the vertex to be visited since we are going to push it onto the queue
                adjList[neighbor].visited = true;
                intq.push(adjList[neighbor].label);

                // we also want to keep track of the path from the start vertex 
                // to the current vertex. This is so that we can trace the path 
                //from the start vertex to the exit vertex once we reach it.
                adjList[neighbor].previous = curr;

            }

        }
    }
    return path;
}