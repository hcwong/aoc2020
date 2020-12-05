#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int bin_search(int start, int end, int rounds, string::iterator *it) {
    int curr_start = start, curr_end = end;
    for (int i = 0; i < rounds; i++, (*it)++) {
        char c = *(*it);
        int median = curr_start + (curr_end - curr_start) / 2;
        if (c == 'L' || c == 'F') curr_end = median;
        else curr_start = median + ((curr_end - curr_start) % 2);
    }
    return curr_start;
}

int parse_pass(string pass) {
    auto it = pass.begin();

    int row = bin_search(0, 127, 7, &it);
    int col = bin_search(0, 7, 3, &it);
    return row * 8 + col;
}

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    int max_id = 0;
    while (getline(ifs, buffer)) {
        max_id = max(max_id, parse_pass(buffer));
    }

    cout << max_id << endl;
}
