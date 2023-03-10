/*
 * CSC-301
 * maze.cpp
 * Fall 2022
 * Eric A. Autry
 * 09/23/22
 */

#include "maze.hpp"

using namespace std;

/*
 * createMaze: creates the maze in a specific format.
 *
 * Note: The maze will be represented as a vector of 0s and 1s. The 0s are open
 *       rooms while the 1s are walls.
 *
 * Note: This function will always return a square maze, i.e., the size() of 
 *       the returned vector will always be a perfect square.
 *
 * INPUTS
 * mazeNum: an int indicating which maze you want
 *     case 0: a small open 3x3 room
 *     case 1: a small 3x3 room with an obstacle
 *     case 2: a larger maze
 *     case 3: a zig-zag maze
 *     case 4: a test to force different behavior from DFS/BFS
 *     case 5: uses Wilson's algorithm to create random mazes
 *     default: same as case 0
 * numChambers: an int for use in case 5 above. This case will create a maze of
 *              size (2*numChambers+1) x (2*numChambers+1).
 *
 * OUTPUTS
 * The vector<int> representing the maze as described above.
 */
vector<int> createMaze(int mazeNum, int numChambers = 12) {
    // Pick the maze.
    switch (mazeNum) {
        case 0: {
            vector<int> maze = {1,1,0,1,1,
                                1,0,0,0,1,
                                1,0,0,0,1,
                                1,0,0,0,1,
                                1,1,0,1,1};
            return maze;
        }
        case 1: {
            vector<int> maze = {1,1,0,1,1,
                                1,0,0,0,1,
                                1,0,1,1,1,
                                1,0,0,0,1,
                                1,1,0,1,1};
            return maze;
        }
        case 2: {
            vector<int> maze = {
                1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,1,
                1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,
                1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,
                1,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,1,
                1,0,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,1,0,0,0,1,
                1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,1,0,1,0,1,1,1,
                1,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,0,1,0,1,0,0,0,1,
                1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,
                1,1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1,
                1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,
                1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,0,1,1,1,0,1,0,1,
                1,0,1,1,1,1,1,1,0,1,0,0,1,1,1,0,1,0,0,0,1,0,1,0,1,
                1,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1,
                1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,0,0,1,0,1,0,1,0,1,
                1,0,0,0,0,1,0,0,0,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,
                1,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,
                1,0,0,1,0,1,0,1,1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,
                1,0,1,1,0,1,0,1,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,
                1,0,1,0,0,1,0,1,0,0,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,
                1,0,1,1,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,1,
                1,0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,1,1,1,0,0,0,1,1,
                1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
            return maze;
        }
        case 3: {
            vector<int> maze = {
                1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
            return maze;
        }
        case 4: {
            vector<int> maze = {
                1,1,1,1,0,1,1,1,1,
                1,0,0,0,0,0,0,0,1,
                1,0,0,0,1,0,0,0,1,
                1,0,0,0,0,0,0,0,1,
                1,0,0,1,0,1,0,0,1,
                1,0,1,1,0,1,1,0,1,
                1,0,1,1,0,1,1,0,1,
                1,0,0,0,0,0,0,0,1,
                1,1,1,1,0,1,1,1,1};
            return maze;
        }
        case 5: {
            vector<int> maze;
            cout << "Not yet implemented!";
            return maze;
        }
        default: {
            vector<int> maze = {1,1,0,1,1,
                                1,0,0,0,1,
                                1,0,0,0,1,
                                1,0,0,0,1,
                                1,1,0,1,1};
            return maze;
        }
    }
}

/*
 * findStartExit: scans the first and last row of the maze to find the ' ',
 *                which are empty rooms - those are the start and exit, so
 *                we return the room number of those locations as a pair
 *
 * INPUTS
 * maze: the maze represented with 0s and 1s (as returned by getMaze)
 * 
 * OUTPUTS
 * A pair of ints corresponding to the room numbers of the start and exit.
 */
pair<int,int> findStartExit(vector<int> &maze) {
    // Get the length of each side.
    int len = sqrt(maze.size());

    // Find the start in the first row and the exit in the last row.
    int startVertex = 0;
    int exitVertex = len*(len-1) - 1;
    for (int i=0; i<len; i++) {
        if (maze[i] == 0) {
            startVertex += i;
        }
        if (maze[i + len*(len-1) - 1] == 0) {
            exitVertex += i;
        }
    }
    pair<int,int> se(startVertex, exitVertex);
    return se;
}

/*
 * printRoomNums prints the maze with the ' ' replaced by the Vertex label.
 *
 * INPUTS
 * maze: the maze represented with 0s and 1s (as returned by getMaze)
 * 
 * OUTPUTS
 * A string representing the maze with room info printed
 */
string printRoomNums(vector<int> &maze) {
    // Get the length of each side.
    int len = sqrt(maze.size());

    // Set the padding for printing the room nums.
    int n = floor(log10(len*len)) + 1;

    // Create the stringstream for the maze.
    stringstream mazeSS;

    // Loop over the entries in the maze and start the ascii drawing.
    for (int room = 0; room < maze.size(); room++) {
        // If we hit the edge of the maze, start a new line.
        if (room % len == 0) {
            mazeSS << endl;
        }

        // Check if we are an open room or a wall.
        if (maze[room] == 0) {
            mazeSS << setw(n) << to_string(room) << " ";
        } else {
            mazeSS << setw(n) << string(n,'X') << " ";
        }
    }

    // Return the string.
    return mazeSS.str();
}

/*
 * makeAdjList: creates an adjacency list for an input maze. Each room 
 *              (including walls) becomes a Vertex object. Neighbors in the 
 *              graph are defined by rook adjacency (NEWS only) in the maze,
 *              but only if both rooms are open (not walls). Walls have no 
 *              neighbors in the graph.
 *
 * INPUTS
 * maze: the maze represented with 0s and 1s (as returned by getMaze)
 * 
 * OUTPUTS
 * A vector<Vertex> that is the adjacency list, where each Vertex.label is its
 * index in this vector.
 */
vector<Vertex> makeAdjList(vector<int> &maze) {
    // Create the adjacency list object.
    vector<Vertex> adjList;

    // Loop over each room in the maze, create a Vertex, push to the adjList.
    for ( int room = 0; room < maze.size(); room++ ) {
        Vertex v(room);
        adjList.push_back(v);
    }

    // Get the length of each side of the maze.
    int len = sqrt(maze.size());

    // Loop over all Vertices and update their neighbor info.
    // Skip the first and last row/col since those are walls.
    for (int row=1; row<len-1; row++) {
        for (int col=1; col<len-1; col++) {
            // Get labels for this vertex and its potential NEWS neighbors.
            int curr = row*len + col;
            int up = (row-1)*len + col;
            int down = (row+1)*len + col;
            int right = row*len + (col+1);
            int left = row*len + (col-1);

            // Check the up room to see if it is open.
            if (maze[up] == 0) {
                adjList[curr].neighbors.push_back(up);
            }

            // Check the down room to see if it is open.
            if (maze[down] == 0) {
                adjList[curr].neighbors.push_back(down);
            }
            
            // Check the left room to see if it is open.
            if (maze[left] == 0) {
                adjList[curr].neighbors.push_back(left);
            }

            // Check the right room to see if it is open.
            if (maze[right] == 0) {
                adjList[curr].neighbors.push_back(right);
            }
        }
    }

    // Look at the start and exit and update (up for exit and down for start).
    pair<int,int> se = findStartExit(maze);
    adjList[se.first].neighbors.push_back(se.first + len);
    adjList[se.second].neighbors.push_back(se.second - len);

    // Return our completed list.
    return adjList;
}

/*
 * checkMaze: will check the correctness of the given path for the input maze.
 *
 * INPUTS
 * maze: the maze represented with 0s and 1s (as returned by getMaze)
 * path: a vector of ints of the room numbers on the path
 * verb: a bool that can allow/supress failure messages
 *
 * OUTPUTS
 * true if valid path, false if invalid path (will print failure messages)
 */
bool checkMaze(vector<int> &maze, vector<int> &path, bool verb) {
    // If the path is empty, it is wrong.
    if ( path.size() == 0 ) {
        if (verb) {
            cout << "Path is empty!" << endl;
        }
        return false;
    }

    // Print out the path.
    if (verb) {
        cout << "Path: ";
        for ( int room : path ) {
            cout << to_string(room) << " ";
        }
        cout << endl;
    }

    // Set our flag to true for now.
    bool isSolved = true;

    // Get the length of each side.
    int len = sqrt(maze.size());

    // Get the start and end rooms.
    pair<int,int> se = findStartExit(maze);

    // Check that the path starts correctly.
    if (*(path.begin()) != se.first) {
        if (verb) {
            cout << "FAILURE: Path needs to start at the start!";
            cout << " Error Room " << to_string(*(path.begin())) << endl;
        }
        isSolved = false;
    }

    // Make sure nothing on the path is a wall or is repeated.
    // Also check that all moves are valid, i.e., no teleporting.
    for ( int ri=0; ri<path.size(); ri++) {
        // Get the current room.
        int room = path[ri];

        // Check for ghosts.
        if (maze[room] == 1) {
            if (verb) {
                cout << "FAILURE: Went through a wall. No ghosts allowed!";
                cout << " Error Room " << to_string(room) << endl;
            }
            isSolved = false;
        }

        // Check for repeats.
        if ( count(path.begin(), path.end(), room) > 1 ) {
            if (verb) {
                cout << "FAILURE: Repeated rooms on path!";
                cout << " Error Room " << to_string(room) << endl;
            }
            isSolved = false;
        }

        // Check the next room in case of teleports.
        if (ri < path.size()-1) {
            int next = path[ri+1];
            if ( next != room+1 and next != room-1 and next != room+len 
                 and next != room-len) {
                if (verb) {
                    cout << "FAILURE: No teleporting! Rooms must be adjacent!";
                    cout << " Error Rooms " << to_string(room) << " and ";
                    cout << to_string(next) << endl;
                }
                isSolved = false;
            }
        }
    }

    // Check that the path exits correctly.
    if (*(--path.end()) != se.second) {
        if (verb) {
            cout << "FAILURE: Path needs to end at the end!";
            cout << " Error Room " << to_string(*(--path.end())) << endl;
        }
        isSolved = false;
    }

    // Return our conclusion.
    return isSolved;
}

/*
 * printMaze: this function takes in the maze and path and creates an ascii
 *            version of the complete maze with path filled in.
 *
 * INPUTS
 * maze: the maze represented with 0s and 1s (as returned by getMaze)
 * path: the path through the maze, a vector of vertex labels
 *
 * OUTPUT
 * mazeStr: a string representing the maze and path in ascii
 */
string printMaze(vector<int> &maze, vector<int> &path) {
    // Get the length of each side.
    int len = sqrt(maze.size());

    // Find the start in the first row and the exit in the last row.
    pair<int,int> se = findStartExit(maze);
    int startVertex = se.first;
    int exitVertex = se.second;

    // Create the empty list of chars to represent our maze.
    vector<char> mazeList;

    // Loop over the entries in the maze and start the ascii drawing.
    for (int room = 0; room < maze.size(); room++) {
        // If we hit the edge of the maze, start a new line.
        if (room % len == 0) {
            mazeList.push_back('\n');
        }

        // Check if we are an open room or a wall.
        if (maze[room] == 0) {
            mazeList.push_back(' ');
        } else {
            mazeList.push_back('X');
        }
    }

    // Update the start/exit of the maze.
    // Note: the offset accounts for the leading empty char at the start and
    //       the newline chars at each line.
    int offset = startVertex/len + 1;
    mazeList[startVertex + offset] = 's';
    offset = exitVertex/len + 1;
    mazeList[exitVertex + offset] = 'e';

    // Now fill in the path.
    for ( int room : path ) {
        if (room != startVertex and room != exitVertex) {
            // Get the offset for this room.
            offset = room/len + 1;

            // Check for repeated vertices on the path, label as R.
            if (mazeList[room + offset] == 'o'
                or
                mazeList[room + offset] == 'G') {
                mazeList[room + offset] = 'R';
            }

            // Fill the path if room was open/usable.
            if (mazeList[room + offset] == ' ') {
                mazeList[room + offset] = 'o';
            }

            // Flag as a 'ghost' if we tried to walk through a wall.
            if (mazeList[room + offset] == 'X') {
                mazeList[room + offset] = 'G';
            }
        }
    }

    // If path doesn't start and exit correctly, fill warnings in maze.
    if (path.size() > 0) {
        if (path[0] != startVertex) {
            offset = startVertex/len + 1;
            mazeList[startVertex + offset] = '!';
        }
        if (path[path.size()-1] != exitVertex) {
            offset = exitVertex/len + 1;
            mazeList[exitVertex + offset] = '!';
        }
    }

    // Return the completed maze string.
    string mazeStr(mazeList.begin(), mazeList.end());
    return mazeStr;
}

/*
 * testMaze: runs DFS and BFS on the given maze and reports success/failure.
 *
 * INPUTS
 * mazeNum: an int indicating which maze you want
 *     case 0: a small open 3x3 room
 *     case 1: a small 3x3 room with an obstacle
 *     case 2: a larger maze
 *     case 3: a zig-zag maze
 *     case 4: a test to force different behavior from DFS/BFS
 *     case 5: uses Wilson's algorithm to create random numRoomsxnumRooms mazes
 * verb: a bool that can allow/supress failure messages
 *
 * OUTPUTS
 * A pair of bools corresponding to passage/failure of DFS and BFS respectively.
 *
 */
pair<bool,bool> testMaze(int mazeNum, bool verb) {
    // Set some flags for checking correctness.
    bool dfsPass = false;
    bool bfsPass = false;

    // DFS
    vector<int> maze = createMaze(mazeNum);
    vector<int> pathDFS;
    if (verb) {
        cout << "Testing DFS on Maze " << mazeNum << ":" << endl;
        cout << printMaze(maze,pathDFS) << endl << endl;
    }
    vector<Vertex> adjList = makeAdjList(maze);
    pair<int,int> se = findStartExit(maze);
    pathDFS = DFS(adjList, adjList[se.first], adjList[se.second]);
    bool isSolved = checkMaze(maze, pathDFS, verb);
    if (verb) {
        cout << printMaze(maze,pathDFS) << endl << endl;
    }
    if (isSolved) {
        dfsPass = true;
        if (verb) {
            cout << "DFS Test Passed!" << endl;
        }
    } else {
        if (verb) {
            cout << "DFS Test Failed!" << endl;
        }
    }

    if (verb) {
        cout << endl;
    }

    // BFS
    maze = createMaze(mazeNum);
    vector<int> pathBFS;
    if (verb) {
        cout << "Testing BFS on Maze " << mazeNum << ":" << endl;
        cout << printMaze(maze,pathBFS) << endl << endl;
    }
    adjList = makeAdjList(maze);
    se = findStartExit(maze);
    pathBFS = BFS(adjList, adjList[se.first], adjList[se.second]);
    isSolved = checkMaze(maze, pathBFS, verb);
    if (verb) {
        cout << printMaze(maze,pathBFS) << endl << endl;
    }
    if (isSolved) {
        bfsPass = true;
        if (verb) {
            cout << "BFS Test Passed!" << endl;
        }
    } else {
        if (verb) {
            cout << "BFS Test Failed!" << endl;
        }
    }

    if (verb) {
        cout << endl;
    }

    pair<bool,bool> passInfo(dfsPass,bfsPass);
    return passInfo;
}

/* main
 * 
 * Runs DFS/BFS on all of the test mazes and checks for correctness.
 *
 * Run this function with the command:
 *     ./maze
 *
 * Note: you can turn on verbosity with a -v flag:
 *     ./maze -v
 *
 */
int main(int argc, char* argv[]) {
    // Check for verbosity.
    bool verbosity = false;
    for ( int ii=1; ii<argc; ii++ ) {
        if ( strcmp(argv[ii], "-v") == 0 ) {
            // Verbosity flag.
            verbosity = true;
        }
    }

    // Track the number of tests passed.
    int dfsPassed = 0;
    int bfsPassed = 0;
    int tried = 0;

    // Maze 0
    pair<bool,bool> maze0info = testMaze(0, verbosity);
    if (maze0info.first) {
        dfsPassed++;
    }
    if (maze0info.second) {
        bfsPassed++;
    }
    tried++;

    // Maze 1
    pair<bool,bool> maze1info = testMaze(1, verbosity);
    if (maze1info.first) {
        dfsPassed++;
    }
    if (maze1info.second) {
        bfsPassed++;
    }
    tried++;

    // Maze 2
    pair<bool,bool> maze2info = testMaze(2, verbosity);
    if (maze2info.first) {
        dfsPassed++;
    }
    if (maze2info.second) {
        bfsPassed++;
    }
    tried++;

    // Maze 3
    pair<bool,bool> maze3info = testMaze(3, verbosity);
    if (maze3info.first) {
        dfsPassed++;
    }
    if (maze3info.second) {
        bfsPassed++;
    }
    tried++;

    // Maze 4
    pair<bool,bool> maze4info = testMaze(4, verbosity);
    if (maze4info.first) {
        dfsPassed++;
    }
    if (maze4info.second) {
        bfsPassed++;
    }
    tried++;

    cout << "Passed " << dfsPassed << "/" << tried << " tests for DFS!" << endl;
    cout << "Passed " << bfsPassed << "/" << tried << " tests for BFS!" << endl;
    cout << endl;
    if (dfsPassed+bfsPassed == 2*tried) {
        cout << "WARNING: Passing all tests only means you solved the mazes.";
        cout << endl;
        cout << "You must still verify that your algs performed correctly!";
        cout << endl;
    }

    return 0;
}