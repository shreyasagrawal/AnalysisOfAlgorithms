/*
 * CSC-301
 * testEdits.cpp
 * Fall 2022
 * Eric A. Autry
 * 11/01/22
 */

#include "testEdits.hpp"

using namespace std;

/*
 * makeEdits: applies the given edits to the input string.
 *
 * INPUTS
 * string src: the source string to edit.
 * vector<Edit> edits: the edits to perform (formatted according to the prompt).
 * bool verbosity: set to true for extra printing if invalid edits given.
 *
 * OUTPUTS
 * string src: the edited src string.
 */
string makeEdits(string src, vector<Edit> edits, bool verbosity) {
    // Loop over the edits.
    for ( Edit ed : edits ) {
        // Check for type of edit.
        if ( ed.label == "match" ) {
            // No edit to make.
            continue;
        } else if ( ed.label == "ins" ) {
            // Perform the insertion.
            string s{ed.destLetter}; // Has to be a string...
            src.insert(ed.location, s);
        } else if ( ed.label == "del" ) {
            // Perform the deletion.
            src.erase(ed.location, 1);
        } else if ( ed.label == "sub" ) {
            // Perform the substitution.
            string s{ed.destLetter}; // Has to be a string...
            src.replace( ed.location, 1, s);
        } else {
            if (verbosity) {
                cout << ed.printEdit(); // Will be invalid and say so.
            }
        }
    }

    return src;
}

/*
 * testCase: runs a specific test.
 *
 * INPUTS
 * string label: the label for the test.
 * string src: the source string for ED.
 * string dest: the destination string for ED.
 * int correctNumEdits: the correct number of edits for this case.
 * bool verbosity: set to true to print test info and results for debugging.
 *
 * OUTPUTS
 * bool: true if test succeeded, false if test failed.
 */
bool testCase(string &label, string &src, string &dest, int correctNumEdits, 
              bool verbosity) {
    // Print the scenario.
    if (verbosity) {
        cout << "--- Performing Test: " << label << " ---" << endl;
        cout << endl;
        cout << "Source String:      " << src << endl;
        cout << "Destination String: " << dest << endl;
        cout << endl;
    }

    // Fill the table.
    vector<int> table = ED(src, dest, false);
    if (verbosity) {
        cout << "Filled DP Table:" << endl;
        cout << printTable(src, dest, table);
    }

    // Calculate optimal number of edits from table.
    int numEdits = getNumEdits(src, dest, table);
    if (verbosity) {
        cout << "Number of Edits Proposed: " << numEdits << endl;
        cout << "Correct Number of Edits:  " << correctNumEdits << endl;
        cout << endl;
    }

    // Find optimal set of edits from table.
    if (verbosity) {
        cout << "Proposed Edits:" << endl;
    }
    vector<Edit> edits = getEdits(src, dest, table);
    if (verbosity) {
        for ( Edit ed : edits ) {
            cout << "\t" << ed.printEdit();
        }
        cout << endl;
    }

    // Perform the proposed edits.
    string edited = makeEdits(src, edits, verbosity);
    if (verbosity) {
        cout << "Edited String: " << edited << endl;
        cout << "Target String: " << dest << endl;
        cout << endl;
    }

    // Check for correctness.
    if ( dest == edited ) {
        return true;
    } else {
        return false;
    }
}

/*
 * getRandStrings: generates two random strings of length m using sig number
 *                 of chars in the alphabet.
 *
 * INPUTS
 * int m: the length of the strings to create.
 * int sig: the number of letters in the alphabet, 0 < sig <= 26.
 *
 * OUTPUTS
 * pair<string, string>: the two random strings.
 */
pair<string, string> getRandStrings(int m, int sig) {
    // Create and seed the rng to ensure reproducibility.
    std::default_random_engine rnd{1};
    std::uniform_int_distribution<int> dist(0, sig-1);

    // Create the reference string of letters to draw from.
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    alphabet.erase(sig, alphabet.length()-sig);

    // Create empty strings, loop and append m letters.
    string src;
    string dest;
    for (int i=0; i<m; i++) {
        src.push_back(alphabet[dist(rnd)]);
        dest.push_back(alphabet[dist(rnd)]);
    }

    // Create the pair and return.
    pair<string, string> strings(src, dest);
    return strings;
}

/*
 * compareRandStrings: computes the average ED or ASM over a number of trials 
 *                     for strings of length m that were generated from an 
 *                     alphabet of size sig.
 *
 * INPUTS
 * int trials: the number of trials to average over.
 * int m: the size of the test strings to generate.
 * int sig: the number of letters in the alphabet, 0 <= sig <= 26.
 * bool useASM: a flag to switch between ED and ASM (true is ASM).
 *
 * OUTPUTS
 * double avg: the average ED or ASM.
 */
double compareRandStrings(int trials, int m, int sig, bool useASM) {
    // For each trial, generate 2 strings, compute ED or ASM, track the avg.
    // Also test ED for correctness as we go...
    double avg = 0;
    bool failed = false;
    for (int t=0; t<trials; t++) {
        pair<string, string> strings = getRandStrings(m, sig);
        vector<int> table = ED(strings.first, strings.second, useASM);
        avg += getNumEdits(strings.first, strings.second, table);
        if (not useASM) {
            vector<Edit> edits = getEdits(strings.first, strings.second, table);
            string edited = makeEdits(strings.first, edits, false);
            if ( strings.second != edited) {
                failed = true;
            }
        }
    }
    avg = avg/trials;

    if (failed) {
        cout << "A TEST FAILED DURING RAND STRING COMPUTATION!" << endl;
    }

    cout << "Performed " << trials << " trials." << endl;
    cout << "Compared strings of length " << m << "." << endl;
    cout << "Generated from an alphabet of " << sig << " letters." << endl;

    if (useASM) {
        cout << "Average ASM as a fraction of the string length: ";
        cout << avg/m << endl;
        cout << "Expected ASM as a fraction of the string length:  ";
        cout << (1-(1/sqrt(sig))) << endl;
    } else {
        cout << "Average ED as a fraction of the string length: ";
        cout << avg/m << endl;
    }

    return avg;
}

/* main
 * 
 * Runs ED on all of the test strings and checks for correctness.
 *
 * Also runs ED and ASM for a variety of strings and alphabets and outputs
 * average distances, which can be used for verifying correct behavior.
 *
 * Run this function with the command:
 *     ./testEdits
 *
 * Note: you can turn on verbosity with a -v flag:
 *     ./testEdits -v
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
    cout << endl;

    // Setup variables for testing.
    string label;
    string src;
    string dest;
    int correctNumEdits;

    // Track the number of tests passed.
    int passed = 0;
    int tried = 0;
    bool correct;

    // --- Test 1 ---
    label = "Class Ex 1";
    src = "spam";
    dest = "pims";
    correctNumEdits = 3;

    correct = testCase(label, src, dest, correctNumEdits, verbosity);

    if ( correct ) {
        cout << "Passed Test: " << label << "!" << endl;
        passed++;
    } else {
        cout << "Failed Test: " << label << "!" << endl;
    }
    cout << endl;
    tried++;

    // --- Test 2 ---
    label = "Class Ex 2";
    src = "libate";
    dest = "flub";
    correctNumEdits = 5;

    correct = testCase(label, src, dest, correctNumEdits, verbosity);

    if ( correct ) {
        cout << "Passed Test: " << label << "!" << endl;
        passed++;
    } else {
        cout << "Failed Test: " << label << "!" << endl;
    }
    cout << endl;
    tried++;

    // --- Test 3 ---
    label = "All Inserts";
    src = "";
    dest = "abc";
    correctNumEdits = 3;

    correct = testCase(label, src, dest, correctNumEdits, verbosity);

    if ( correct ) {
        cout << "Passed Test: " << label << "!" << endl;
        passed++;
    } else {
        cout << "Failed Test: " << label << "!" << endl;
    }
    cout << endl;
    tried++;

    // --- Test 4 ---
    label = "All Deletes";
    src = "abc";
    dest = "";
    correctNumEdits = 3;

    correct = testCase(label, src, dest, correctNumEdits, verbosity);

    if ( correct ) {
        cout << "Passed Test: " << label << "!" << endl;
        passed++;
    } else {
        cout << "Failed Test: " << label << "!" << endl;
    }
    cout << endl;
    tried++;

    // --- Test 5 ---
    label = "All Subs";
    src = "aaa";
    dest = "bbb";
    correctNumEdits = 3;

    correct = testCase(label, src, dest, correctNumEdits, verbosity);

    if ( correct ) {
        cout << "Passed Test: " << label << "!" << endl;
        passed++;
    } else {
        cout << "Failed Test: " << label << "!" << endl;
    }
    cout << endl;
    tried++;

    // Report Results.
    cout << "Passed " << passed << "/" << tried << " tests for ED!" << endl;
    cout << endl;

    // Perform the ED and ASM tests with random strings.
    compareRandStrings(30, 300, 4, false);  // ED on genomes.
    cout << endl;
    compareRandStrings(30, 300, 4, true);   // ASM on genomes.
    cout << endl;
    compareRandStrings(30, 300, 26, false); // ED on English words.
    cout << endl;
    compareRandStrings(30, 300, 26, true);  // ASM on English words.
    cout << endl;

    return 0;
}