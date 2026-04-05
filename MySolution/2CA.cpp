// Written by: Simion Cartis

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {
    string fileName;
    if (argc == 2) {
        fileName = argv[1];
    } else {
        return 1;
    }
    cout << fileName;
    return 0;
}