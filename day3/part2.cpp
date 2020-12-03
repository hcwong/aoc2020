#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utils.hpp>

using namespace std;

int run_slope(pair<int, int>, int, int, vector<vector<char> > &matrix);

int main() {
    auto matrix = read_input();
    int rows = matrix.size();
    int cols = matrix[0].size();
    long trees = 1;

    vector<pair<int, int> > slopes = {{1,1}, {1,3}, {1,5}, {1,7}, {2,1}};

    for (auto &slope: slopes)
        trees *= run_slope(slope, rows, cols, matrix);

    cout << trees << endl;
}

int run_slope(pair<int, int> slope, int rows, int cols, vector<vector<char> > &matrix) {
    int x = slope.first, y = slope.second, i = 0, j = 0, trees = 0;

    for (; i < rows; i += x) {
        // Do a mod operation here to represent the pattern repeating to the right an infinite number of times
        if (matrix[i][j % cols] == '#') trees++;
        j += y;
    }

    return trees;
}
