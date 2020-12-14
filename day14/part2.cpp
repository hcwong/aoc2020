#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

u_int64_t to_decimal(int bit_arr[36]) {
    u_int64_t sum = 0, base = 1;

    for (int i = 35; i >= 0; i--, base *= 2) {
       sum += (bit_arr[i] * base);
    }

    return sum;
}

void add_floating_addr(int idx, u_int64_t value, map<u_int64_t, u_int64_t> &memory, int mem_arr[36]) {
    for (int i = idx; i < 36; i++) {
        if (mem_arr[i] == 2) {
            mem_arr[i] = 0;
            add_floating_addr(i + 1, value, memory, mem_arr);
            mem_arr[i] = 1;
            add_floating_addr(i + 1, value, memory, mem_arr);
            mem_arr[i] = 2;
            return;
        }
    }

    u_int64_t addr = to_decimal(mem_arr);
    memory[addr] = value;
}

void mask_val(string mask, u_int64_t value, u_int64_t addr, map<u_int64_t, u_int64_t> &memory) {
    int mem_arr[36] = {0};
    int idx = 35;

    while (addr > 0) {
        mem_arr[idx--] = addr % 2;
        addr /= 2;
    }

    for (int i = 0; i < 36; i++) {
        if (mask[i] == '1')
            mem_arr[i] = 1;
        else if (mask[i] == 'X')
            mem_arr[i] = 2;
    }

    // Use recursion w/ backtracking to generate all the possible floating addresses
    add_floating_addr(0, value, memory, mem_arr);
}

int main() {
    ifstream ifs("input.txt");
    string buffer;
    string mask;
    map<u_int64_t, u_int64_t> memory;

    while (getline(ifs, buffer)) {
        if (string(buffer.begin(), buffer.begin() + 4) == "mask") {
            vector<string> mask_vec;
            boost::split(mask_vec, buffer, boost::is_any_of("="));
            mask = mask_vec[1];
            boost::trim(mask);
        } else {
            // Now handle the normal mem allocation
            vector<string> mask_vec;
            boost::split(mask_vec, buffer, boost::is_any_of("="));
            string value_str = mask_vec[1];
            boost::trim(value_str);
            u_int64_t value = stoull(value_str);
            string mem_str = mask_vec[0];
            u_int64_t addr = stoull(string(mem_str.begin() + 4, prev(mem_str.end())));
            mask_val(mask, value, addr, memory);
        }
    }

    // Get the sum now
    u_int64_t res = 0;
    for (auto it = memory.begin(); it != memory.end(); it++)
        res += it->second;

    cout << res << endl;
}
