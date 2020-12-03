#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<char> > read_input();

int main() {
    auto matrix = read_input();
    int rows = matrix.size();
    int cols = matrix[0].size();
    int i = 0, j = 0, trees = 0;

    for (; i < rows; i++) {
        // Do a mod operation here to represent the pattern repeating to the right an infinite number of times
        if (matrix[i][j % cols] == '#') trees++;
        j += 3;
    }

    cout << trees << endl;
}

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
