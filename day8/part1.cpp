#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>

using namespace std;

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    vector<pair<string, int> > instructions;
    set<int> seen;
    while (getline(ifs, buffer)) {
        vector<string> instruction_vec;
        boost::split(instruction_vec, buffer, boost::is_any_of(" "));

        string instruction = instruction_vec[0];
        int sign = instruction_vec[1][0] == '-' ? -1 : 1;
        int value = stoi(string(next(instruction_vec[1].begin()),
                                instruction_vec[1].end())) * sign;

        instructions.push_back(make_pair(instruction, value));
    }

    int pc = 0, accum = 0;
    while (seen.count(pc) == 0) {
        string instruction = instructions[pc].first;
        int value = instructions[pc].second;

        seen.insert(pc);

        if (instruction == "nop") {
            pc++;
        } else if (instruction == "acc") {
            pc++;
            accum += value;
        } else if (instruction == "jmp") {
            pc += value;
        }
    }

    cout << accum << endl;
}
