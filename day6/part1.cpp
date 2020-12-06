#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    set<char> current_entry;
    int count = 0;

    while (getline(ifs, buffer)) {
        if (buffer == "") {
            count += current_entry.size();
            current_entry.clear();
            continue;
        }

        // Now parse the line
        for (char &c: buffer) {
            current_entry.insert(c);
        }
    }

    // Handle last passport to prevent off by one error
    count += current_entry.size();

    cout << count << endl;
}
