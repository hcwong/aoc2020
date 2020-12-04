#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    map<string, string> current_entry;
    int passports = 0;
    while (getline(ifs, buffer)) {
        if (buffer == "") {
            current_entry.erase("cid");
            if (current_entry.size() == 7) passports++;
            current_entry.clear();
            continue;
        }

        // Now parse the line
        vector<string> fields_in_line;
        boost::split(fields_in_line, buffer, boost::is_any_of(" "));
        for (auto &field: fields_in_line) {
            vector<string> field_vec;
            boost::split(field_vec, field, boost::is_any_of(":"));
            string key = field_vec[0], value = field_vec[1];
            current_entry[key] = value;
        }
    }

    // Handle last passport to prevent off by one error
    current_entry.erase("cid");
    if (current_entry.size() == 7) passports++;

    cout << passports << endl;
}
