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

u_int64_t mask_val(string mask, long value) {
    int bit_arr[36] = {0};
    int idx = 35;

    while (value > 0) {
        bit_arr[idx--] = value % 2;
        value /= 2;
    }

    for (int i = 0; i < 36; i++) {
        if (mask[i] == '0' || mask[i] == '1')
            bit_arr[i] = mask[i] - '0';
    }

    return to_decimal(bit_arr);
}

int main() {
    ifstream ifs("input.txt");
    string buffer;
    string mask;
    map<long, u_int64_t> memory;

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
            long value = stol(value_str);
            string mem_str = mask_vec[0];
            long addr = stol(string(mem_str.begin() + 4, prev(mem_str.end())));
            memory[addr] = mask_val(mask, value);
        }
    }

    // Get the sum now
    u_int64_t res = 0;
    for (auto it = memory.begin(); it != memory.end(); it++)
        res += it->second;

    cout << res << endl;
}
