#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<char> > read_input() {
    ifstream ifs("input1.txt");
    char tempchar;
    string buffer;
    vector<vector<char> > result;
    while (getline(ifs, buffer)) {
        istringstream iss(buffer);
        vector<char> curr_vec;
        while (iss >> tempchar) {
           curr_vec.push_back(tempchar);
        }
        result.push_back(curr_vec);
    }
    return result;
}
