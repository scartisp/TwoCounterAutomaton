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
    while (true) {
        cout << (readInput() ? "ACCEPT" : "REJECT") << endl;
    }
    return 0;
}

bool readInput() {
    string currState = "#";
    int counterOneValue = 0;
    int counterTwoValue = 0;
    string input;
    cin >> input;
    bool change = true;

    while (change) {
        cout << currState << ", " << input << ", " << counterOneValue << ", " << counterTwoValue << endl;
        change = false;
        string leadingSymbol = (input.size() > 0) ? string(1,input.at(0)) : leadingSymbol = "";
        //string leadingSymbol(1,input.at(0));
        Transition* epsilonTrans = nullptr;
        //cout << transitions.size();
        for (const auto& t: transitions) {
            if (validTrans(t, leadingSymbol, counterOneValue, counterTwoValue, currState)) {
                if (t.input == " ") {
                   epsilonTrans = nullptr;
                    epsilonTrans = new Transition(t);
                } else {
                    makeChange(t, currState, counterOneValue, counterTwoValue);
                    input = input.erase(0,1);
                    change = true;
                    break;
                }
            }
        }
        if (epsilonTrans != nullptr && !change) {
          //  cout << "episoln" << endl;
            makeChange(*epsilonTrans, currState, counterOneValue, counterTwoValue);
            change = true;
        }
        delete epsilonTrans;
    }
   // cout << change << endl;
    //cout << currState << ", " << input.size() << ", " << counterOneValue << ", " << counterTwoValue << endl;
    if (counterOneValue == 0 && counterTwoValue == 0 && input == "")
        return true;
    return false;
}

void makeChange(Transition transition, string& currState, int& counterOneValue, int& counterTwoValue) {
    currState = transition.nextState;
    if (transition.changeCounterOne == '+') {
        ++counterOneValue;
    } else if (transition.changeCounterOne == '-' && counterOneValue > 0) {
        --counterOneValue;
    }
    if (transition.changeCounterTwo == '+') {
        ++counterTwoValue;
    } else if (transition.changeCounterTwo == '-' && counterTwoValue > 0) {
        --counterTwoValue;
    }
    //cout << counterTwoValue << endl;
}

bool validTrans(Transition transition, string leadingSymbol,
    int counterOneValue, int counterTwoValue, string currState) {
        // if (transition.currState == "#copy_back") {
        //     cout << (transition.currState == currState);
        //     cout << ()
        // }
        if (transition.counterOneState == '=' && counterOneValue != 0) {
        return false;
       } else if (transition.counterOneState == '>' && counterOneValue == 0) {
        return false;
       } else if (transition.counterTwoState == '=' && counterTwoValue != 0) {
        return false;
       } else if (transition.counterTwoState == '>' && counterTwoValue == 0) {
        return false;
       } else if (transition.currState != currState) {
        return false;
       } else if (transition.input != leadingSymbol && transition.input != " ") {
        return false;
       } else {
        return true;
       }
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
        t.counterOneState = leftParts[2].at(0);
        t.counterTwoState = leftParts[3].at(0);
        t.nextState = rightParts[0];
        t.changeCounterOne = rightParts[1].at(0);
        t.changeCounterTwo = rightParts[2].at(0);
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