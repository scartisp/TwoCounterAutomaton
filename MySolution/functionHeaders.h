#ifndef _FUNCTIONHEADERS_H_
#define _FUNCTIONHEADERS_H_
#include <string>
using std::string;
#include <vector>
using std::vector;

/**
 * struct for the transitions
 */
struct Transition {
    // info from left side of a line
    string currState;
    string input;
    char counterOneState;
    char counterTwoState;
    // infro from right side of a line
    string nextState;
    char changeCounterOne;
    char changeCounterTwo;

    Transition() = default; //default constructor
    Transition(const Transition& t) {
        this->currState = t.currState;
        this->input = t.input;
        this->counterOneState = t.counterOneState;
        this->counterTwoState = t.counterTwoState;

        this->nextState = t.nextState;
        this->changeCounterOne = t.changeCounterOne;
        this->changeCounterTwo = t.changeCounterTwo;
    }
};
/**
 * function that does the simulation. consumes the input and determines if it rejects or fails
 * @param {string} the input string that will be read by the 2ca simulation 
 * @return {bool} boolean for if it rejects or accepts (reject= false, accept = true)
 */
bool readInput(string input);
/**
 * helper function for readInput that determines the next state and what counters to change/how
 * @param {Transition} transition that is taken by the readInput function
 * @param {string&} the name of the state which becomes the new current state
 * @param {int&} value held by counter 1
 * @param {int&} value held by counter 2
 */
void makeChange(Transition transition, string& currState, int& counterOneValue, int& counterTwoValue);
/**
 * helper function for readInput that determines if a transition is valid or not
 * @param {Transition} the transition that we are checking for validness
 * @param {string} the first character of the input string (as a string)
 * @param {int} value held by counter 1
 * @param {int} value held by counter 2
 * @param {string} the current state of the 2CA
 * @return {bool} boolean for if a transition is valid or not
 */
bool validTrans(Transition transition, string leadingSymbol, int counterOneValue,
                int counterTwoValue, string currState);

/**
 * function for creating the vector of Transition structs out of the .txt file given
 * as an argument to this program
 * @param {string} the name of the .txt file to read from
 */
void create2CA(string fileName);
/**
 * helper function to split each half of a line into their relevant pieces
 * (the halves are delineated) by a cama
 * @param {string} the half of a string that we will extract needed info from
 * @return a vector of strings containing the relevant parts pieces
 */
vector<string> splitByCama(string line);
/**
 * helper function to trim white spaces from parts of a line
 * @param {string} the string which will have its white spaces removed
 * @return {string} the version of the string that has its white spaces removed.
 * in the case that there is an epsilon transition (denoted by two camas with 0 or more white spaces)
 * this function returns a whitespace to denote the epsilon transition
 */
string trim(string line);
#endif