#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> seen;
    int size = 6;
    int input[6] = {14,8,16,0,1,17};
    int i, to_speak = 0, target = 30000000;

    for (i = 1; i <= size; i++) {
        to_speak = seen.count(input[i - 1]);
        seen[input[i - 1]] = i;
    }

    // Brute Force :)
    for (; i < target; i++) {
        if (seen.count(to_speak) == 0) {
            seen[to_speak] = i;
            to_speak = 0;
        } else {
            int next_to_speak = i - seen[to_speak];
            seen[to_speak] = i;
            to_speak = next_to_speak;
        }
    }

    cout << to_speak << endl;
}
