/*
 * CSC-301
 * project3.cpp
 * Spring 2023
 * Shrey Agrawal
 * Due Date: 03.17.2023
 */

#include "project3.hpp"

using namespace std;

/*
 * createAdjacencyMatrix
 * Purpose: make a matrix of the negative log of exchange rates so that we can identify arbitrage
 * INPUT:
 * rates is a 1D array representing the exchange rates matrix
 * currencies is an array of currency label strings
 * OUTPUT:
 * adjMatrix is a 1D array representing the negative log of the exchange rates so that it can be used for arbitrage
 */
vector<double> createAdjacencyMatrix(vector<double> &rates, vector<string> &currencies) 
{
    vector<double> adjMatrix(rates);
    int n = currencies.size(); //this will tell us how many currencies we have

    // for (int i = 0; i<rates.size(); i++){
    //     cout << rates[i];
    //     cout << "\n";
    // }
    // Since the rates matrix has 1's in the place where the currecy is the same, 
    // we don't need to account for any special case where the row=col since that equals 1,
    // and negative log of 1 is 0, which is what we want for same currencies in our
    for(int r=0; r<n; r++){
        for(int c=0; c<n; c++){
                adjMatrix[r*n+c] = -log(rates[r*n+c]); // negative log of exchange rate
            }
        }
    return adjMatrix;
}

/*
 * detectArbitrage
 * This function is there to detects arbitrage opportunities 
 * INPUTS:
 * adjMatrix: a vector that represents the adjacency matrix of the graph, where the value adjMatrix[r*n+c] 
 * represents the weight of the edge from vertex r to vertex c in the graph. In this case, the exchange rate
 * currencies: a vector of strings that represents the currencies.
 * tol: a double that specifies the acceptable difference between actual and computed exchange rates.
 * OUTPUT: a vector that represents the negative cost cycle in the graph, if one exists, else empty
 */
vector<int> detectArbitrage(vector<double> &adjMatrix, vector<string> &currencies, double tol) 
{

    // Get the number of vertices and initialize the dist and prev values.
    int n = currencies.size();
    // To store distance info - offers. if this changes then, neg cost cycle
    vector<double> distances( n, numeric_limits<double>::infinity() );
    // To keep track of the previous value of a vertex in a path. will be used for traceback until cycle is found
    vector<int> previous( n, -1 );

    // in currencies, at index k is the currency at r/c k in adjMatrix
    
    //implementing Bellman-Ford
    // we know the correct distance of the first vertex in the graph is 0, so:
    distances[0] = 0;

    // A vertex in our graph is the currency. Doing |V|-1 iterations of bellman-ford
    for (int i = 0; i<n-1; i++){
        // now we check the distances with each vertex in the graph, and there are n vertices
        // the adjMatrix is of size nXn, so to get through the entire matrix, look at each neighbour
        // and find the correct weight, we do a nested for loop
        for (int r =0; r<n;r++){
            for (int c = 0; c<n;c++){
                if(distances[c]>distances[r]+adjMatrix[r*n+c]+tol){
                    //we accept a better offer
                    distances[c] = distances[r]+adjMatrix[r*n+c];
                    previous[c] = r;
                }
            }
        }
    }
    // Create the cycle variable
    vector<int> cycle;

    // After |V| - 1 iterations of the bellman ford algorithm, we want to do 1 more 
    // to see if distance change. if it did, there is a negative cost cycle!
    for (int r =0; r<n;r++){
        for (int c = 0; c<n;c++){
            if(distances[c]>distances[r]+adjMatrix[r*n+c]+tol){ //if there is a better offer, negative cost cycle has been found
            // we need to find the cycle now. this neighbor (c) is part of the cycle.
            // To find the cycle, we start at c and keep following the previous vertex until we reach c again.
            // Then, we reverse the order of the vertices in the cycle and return it.
            // To reach starting vertex
            for(int i=0; i<n; i++){
                c = previous[c];
            }
            // Store the starting vertex of the cycle.
            int start = c;
            // Trace back the cycle from the starting vertex until it reaches 
            // the starting vertex again and add each vertex to the cycle
            do{
                cycle.push_back(start);
                start = previous[start];
                
            }while(c!=start);
            // Adding the final vertex to the cycle
            cycle.push_back(c);
            // reversing the order of the cycle.
            reverse(cycle.begin(), cycle.end());
            return cycle;
            }
        }
    }



    // Return the cycle.
    return cycle;
}



