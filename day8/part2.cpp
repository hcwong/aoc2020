#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <stack>
#include <boost/algorithm/string.hpp>

using namespace std;

int run(vector<pair<string, int> > &instructions, bool *is_terminate) {
    set<int> seen;
    int pc = 0, accum = 0, L = instructions.size();

    while (seen.count(pc) == 0 && pc < L) {
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

    if (pc >= L) {
        *is_terminate = true;
        return accum;
    }

    return 0;
}

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    vector<pair<string, int> > instructions;
    set<int> seen;
    stack<int> stk;
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
        stk.push(pc);

        if (instruction == "nop") {
            pc++;
        } else if (instruction == "acc") {
            pc++;
            accum += value;
        } else if (instruction == "jmp") {
            pc += value;
        }
    }

    // Record the instructions that have been executed using a stack
    // Change them if necessary, and then rerun the program to see if it terminates
    bool found_target = false;
    while (!found_target && !stk.empty()) {
        auto top = stk.top(); stk.pop();
        auto instruction = instructions[top].first;
        vector<pair<string, int> > instructions_copy = instructions;

        if (instruction == "acc") {
           continue;
        }

        if (instruction == "jmp")
           instructions_copy[top] = make_pair("nop", instructions[top].second);
        else if (instruction == "nop")
           instructions_copy[top] = make_pair("jmp", instructions[top].second);

        bool is_terminate = false;
        int res = run(instructions_copy, &is_terminate);

        found_target = is_terminate;
        if (found_target) cout << res << endl;
    }
}
