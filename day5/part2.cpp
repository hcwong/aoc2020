#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

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
    set<int> seen;
    while (getline(ifs, buffer)) {
        int curr_id = parse_pass(buffer);
        max_id = max(max_id, curr_id);
        seen.insert(curr_id);
    }

    // Now find the missing seat, which is sandwiched between two occipied seats.
    for (int i = 0; i < 127 * 8 + 8; i++) {
        if (seen.count(i) == 0 && seen.count(i-1) == 1 && seen.count(i+1) == 1) cout << i << endl;
    }
}
