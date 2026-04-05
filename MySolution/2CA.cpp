// Written by: Simion Cartis

#include <fstream>
#include <iostream>
#include <string>
#include<vector>
#include<sstream>
#include "functionHeaders.h"

using namespace std;
//global variables
vector<Transition> transitions;

int main(int argc, char* argv[]) {
    string fileName;
    if (argc == 2)
        fileName = argv[1];
    else
        return 1;
    create2CA(fileName);
    return 0;
}

void create2CA(string fileName) {
    Transition t;
    ifstream file(fileName);
    if (!file) {
        cerr << "no file found";
        return;
    }
    string line;

    while (getline(file, line)) {
        // remove any comments from a line
        size_t comment = line.find("//");
        if (comment != string::npos)
            line = line.substr(0, comment);
        if (line.find_first_not_of(" \t") == string::npos)
            continue;  // skips following code if line is just a comment

        size_t arrowPos = line.find("->");
        if (arrowPos == string::npos) {
            cerr << "error during parsing";
            return;
        }
        //get the two halfs of the line and extract the needed info
        string left = trim(line.substr(0, arrowPos));
        string right = trim(line.substr(arrowPos+2));
        if (left.front() == '(') {left.erase(0, 1);}
        if (left.back() == ')') {left.pop_back();} //get rid of the first () for each part
        if (right.front() == '(') {right.erase(0, 1);}
        if (right.back() == ')') {right.pop_back();}
        vector<string> leftParts = splitByCama(left);
        vector<string> rightParts = splitByCama(right);
        //add info to the Transistion struct
        t.currState = leftParts[0];
        t.input = leftParts[1];
        t.counterOneStat = leftParts[2];
        t.counterTwoStat = leftParts[3];
        t.nextState = rightParts[0];
        t.changeCounterOne = rightParts[1];
        t.changeCounterTwo = rightParts[2];
        transitions.push_back(t);
    }
    file.close();
}

vector<string> splitByCama(string line) {
    vector<string> parts;
    string part;
    stringstream lineStream(line);
    while(getline(lineStream, part, ',')) {
        parts.push_back(trim(part));
    }
    return parts;
}

string trim(string line) {
    size_t start = line.find_first_not_of(" \t");
    size_t end = line.find_last_not_of(" \t");
    if (start == string::npos) {
        return (" ");
    }
    return line.substr(start, end-start+1); // need to add 1 because valid string could only be 1 char
                                            // also because 0 indexed, so for trim the left and right
                                            // line halves, 0 - end + 1 gets you everything you need
}