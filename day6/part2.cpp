#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    map<char, int> current_entry;
    int count = 0;
    int persons_in_grp = 0;

    while (getline(ifs, buffer)) {
        if (buffer == "") {
            for (auto it = current_entry.begin(); it != current_entry.end(); it++) {
                if (it->second == persons_in_grp) count++;
            }

            current_entry.clear();
            persons_in_grp = 0;
            continue;
        }

        // Now parse the line
        for (char &c: buffer) {
            if (current_entry.count(c) == 0) current_entry[c] = 1;
            else current_entry[c]++;
        }
        persons_in_grp++;
    }

    // Handle last passport to prevent off by one error
    for (auto it = current_entry.begin(); it != current_entry.end(); it++) {
        if (it->second == persons_in_grp) count++;
    }

    cout << count << endl;
}
