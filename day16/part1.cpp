#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

const string YOUR_TICKET = "your ticket";
const string NEARBY_TICKETS = "nearby tickets";

int main() {
    ifstream ifs("input.txt");
    string buffer;
    vector<vector<pair<int, int> > > ranges;
    int error_rate = 0;

    while (getline(ifs, buffer)) {
        if (buffer == "" || buffer.find(YOUR_TICKET) != string::npos
            || buffer.find(NEARBY_TICKETS) != string::npos)
            continue;

        if (buffer.find(':') == string::npos) {
            vector<string> values;
            boost::split(values, buffer, boost::is_any_of(","));

            for (auto value : values) {
                int int_value = stoi(value);
                bool is_valid = false;

                for (auto &range : ranges) {
                    for (auto &range_option : range) {
                        if (int_value >= range_option.first
                            && int_value <= range_option.second)
                            is_valid = true;
                    }
                }

                if (!is_valid) {
                    error_rate += int_value;
                }
            }
        } else {
            vector<string> buffer_arr;
            boost::split(buffer_arr, buffer, boost::is_any_of(":"));
            string value_str = buffer_arr[1];
            boost::trim(value_str);

            vector<string> values;
            boost::split_regex(values, value_str, boost::regex("or"));

            vector<pair<int, int> > range;
            for (auto value : values) {
                boost::trim(value);
                int pos = value.find('-');
                int first_val = stoi(string(value.begin(), value.begin() + pos));
                int second_val = stoi(string(value.begin() + pos + 1, value.end()));
                range.push_back(make_pair(first_val, second_val));
            }

            ranges.push_back(range);
        }
    }

    cout << error_rate << endl;
}
