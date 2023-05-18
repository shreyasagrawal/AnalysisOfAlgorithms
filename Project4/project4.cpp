/*
 * CSC-301
 * project4.cpp
 * Spring 2023
 *
 * Shrey Agrawal
 * Date: Due 04/17/2023
 */

#include "project4.hpp"

using namespace std;

/*
 * ED: only responsible for filling in the DP table.
 */
vector<int> ED(string &src, string &dest, bool useASM) {
    // Get string lengths for ease of use.
    int n = src.length();
    int m = dest.length();
    int numCols = m+1;

    // Setup the table, size (n+1)x(m+1), filled with 0s.
    // dynamic programming set up
    vector<int> table( (n+1)*(m+1), 0 );

    // start at the back of the strings. start with comparing the last letter of both strings.
    // if they are the same, then we don't need to make an edit. 
    // if they are different, then we need to make an edit. insert, delete, or substitute.

    // first row and column of the table will be the base case.
    // the top left cell will remain 0. 
    // the first row will be the number of insertions needed to change the source string to the destination string.
    // the first column will be the number of deletions needed to change the source string to the destination string.
    
    // fill in the first row and column of the table, which will be the base case from the recursive solution.
    for (int i = 0; i<n+1; i++){
        for (int j = 0; j<m+1; j++){
            if (i==0){
                if (useASM){
                    // use ASM
                    table[i*numCols + j] = 0;
                }
                else
                {
                    table[i*numCols + j] = j;
                }
            }
            if (j==0){
                table[i*numCols + j] = i;
            }
        }
    }

    // fill in the rest of the table. we need the left, above, and diagonal left and above cells to be filled out before we can fill out a certain cell.
    // the final solution will be in the bottom right corner of the table.
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < m+1; j++) {
            // if the letters are the same, then we don't need to make an edit.
            if (src[i-1] == dest[j-1]) {
                table[i*numCols + j] = table[(i-1)*numCols + (j-1)];
            }
            else {
                // if the letters are different, then we need to make an edit. insert, delete, or substitute, whichever is the minimum.
                // using row major order
                table[i*numCols + j] = 1 + min(table[(i-1)*numCols + (j-1)], min(table[(i-1)*numCols + j], table[i*numCols + (j-1)]));
            }
        }
    }

    return table;
}

/*
 * getNumEdits: for determining minumum number of edits. Levenshtein distance.
 */
int getNumEdits(string &src, string &dest, vector<int> &table) {
    int numEdits;

    // get the last cell of the table (bottom right). this is the final solution.
    numEdits = table[(src.length())*(dest.length()+1) + dest.length()];

    return numEdits;
}

/*
 * getEdits: for determining the actual edits given the table.
 */
vector<Edit> getEdits(string &src, string &dest, vector<int> &table) {
    vector<Edit> edits;
    int i = src.length();
    int j = dest.length();
    int numCols = j+1;

    // start at the bottom right corner of the table.
    // if the cell came from the cell diagonally above and to the left of it, then we need to substitute the letter.
    // if the cell came from the cell above it, then we need to delete the letter.
    // if the cell came from the cell to the left of it, then we need to insert the letter.
    // if the cell is the same as the cell diagonally above and to the left of it, then we don't need to make an edit.
    
    while (i != 0 && j != 0)
    {
        // checking if diagonal is 1 less - subsitute
        if (table[i*numCols + j] == table[(i-1)*numCols + (j-1)] + 1) {
            // we have a substitution
            Edit ed2("sub", src[i-1], dest[j-1], i-1);
            edits.push_back(ed2);
            // move diagonally up and to the left
            j--;
            i--;
        }
        // checing if above is 1 less - delete
        else if (table[i*numCols + j] == table[(i-1)*numCols + j] + 1) {
            // we have a deletion
            Edit ed3("del", src[i-1], dest[j-1], i-1);
            edits.push_back(ed3);
            // move up
            i--;
        }

        // checking if to the left is 1 less - insert
        // the location is i because you want to insert 1 after where you are currently
        else if (table[i*numCols + j] == table[i*numCols + (j-1)] + 1) {
            // we have an insertion
            Edit ed4("ins", src[i-1], dest[j-1], i);
            edits.push_back(ed4);
            // move left
            j--;
        }

        // nothing - the diagonal is the same and none of the other cases are true
        else if (table[i*numCols + j] == table[(i-1)*numCols + (j-1)]) {
            //we have a match
            Edit ed1("match", src[i-1], dest[j-1], i-1);
            edits.push_back(ed1);
            // move diagonally up and to the left
            j--;
            i--;
        }
    }

    // taking care of the cases when i = 0 or j = 0, and we need to do a bunch of insertions or deletions - base case
    while (j!=0){
        // we need to insert the letter
        // the location is i because you want to insert 1 after where you are currently
        Edit ed5("ins", src[i-1], dest[j-1], i);
        edits.push_back(ed5);
        j--;
    }

    while (i!=0){
        // we need to delete the letter
        Edit ed6("del", src[i-1], dest[j-1], i-1);
        edits.push_back(ed6);
        i--;
    }

    return edits;
}

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
string printTable(string &src, string &dest, vector<int> &table) {
    // Create the stringstream for the table.
    stringstream tableString;

    // Shift the first row for the dest letters and write the letters.
    // tableString << setw(labelWidth) << fixed;
    tableString << " " << " " << " " << " ";
    for (int j=0; j<dest.length(); j++) {
        // tableString << setprecision(prec) << setw(numWidth) << fixed;
        tableString << dest[j] << " ";
    }
    tableString << endl;

    // Write each line of the table, with the proper src letter at front.
    for (int i=0; i<src.length()+1; i++) {
        // tableString << setw(labelWidth) << fixed;
        if (i > 0) {
            tableString << src[i-1] << " ";
        } else {
            tableString << " " << " ";
        }
        for (int j=0; j<dest.length()+1; j++) {
            // tableString << setprecision(prec) << setw(numWidth) << fixed;
            tableString << table[i*(dest.length()+1) + j] << " ";
        }
        tableString << endl;
    }
    tableString << endl;

    return tableString.str();
}