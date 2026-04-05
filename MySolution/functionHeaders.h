#ifndef _FUNCTIONHEADERS_H_
#define _FUNCTIONHEADERS_H_
#include<string>
using std::string;
#include<vector>
using std::vector;

/**
 * struct for the transitions
 */
struct Transition {
    //info from left side of a line
    string currState;
    string input;
    string counterOneStat;
    string counterTwoStat;
    // infro from right side of a line
    string nextState;
    string changeCounterOne;
    string changeCounterTwo;

};
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