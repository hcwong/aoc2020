#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

bool is_valid_hair_color(string color) {
    string value = string(color.begin() + 1, color.end());
    return color.size() == 7 && color[0] == '#'
        && value.find_first_not_of("0123456789abcdef") == string::npos;
}

bool is_valid_height(string height) {
    // gets the last 2 characters
    string unit = string(height.end() - 2, height.end());
    if (unit != "cm" && unit != "in") return false;

    int value = stoi(string(height.begin(), height.end() - 2));

    if (unit == "cm") return value >= 150 && value <= 193;
    else if (unit == "in") return value >= 59 && value <= 76;
    else return false;
}

bool is_valid(map<string, string> entry) {
    set<string> eye_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

    if (entry.count("byr") == 0) return false;
    if (entry.count("iyr") == 0) return false;
    if (entry.count("eyr") == 0) return false;

    int byr = stoi(entry["byr"]), iyr = stoi(entry["iyr"]), eyr = stoi(entry["eyr"]);
    if (byr < 1920 || byr > 2002 || iyr < 2010 || iyr > 2020 || eyr < 2020 || eyr > 2030)
        return false;

    if (entry.count("pid") == 0) return false;
    if (entry["pid"].find_first_not_of("0123456789") != string::npos ||
        entry["pid"].size() != 9) return false;

    if (entry.count("ecl") == 0) return false;
    if (eye_colors.count(entry["ecl"]) == 0) return false;

    if (entry.count("hcl") == 0 || !is_valid_hair_color(entry["hcl"])) return false;

    if (entry.count("hgt") == 0 || !is_valid_height(entry["hgt"])) return false;

    return true;
}

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    map<string, string> current_entry;
    int passports = 0;
    while (getline(ifs, buffer)) {
        if (buffer == "") {
            current_entry.erase("cid");
            if (is_valid(current_entry)) passports++;
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
    if (is_valid(current_entry)) passports++;

    cout << passports << endl;
}
