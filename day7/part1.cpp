#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

class Bag {
    string name;
    public:
        vector<pair<Bag *, int> > contained_in;
        Bag(string name) {
            this->name = name;
        };
        Bag() {
            this->name = "";
        };
        string get_name() { return this->name; };
};

int dfs(map<string, Bag *> bags, string target) {
    set<string> visited;

    Bag *root = bags[target];
    visited.insert(target);
    stack<Bag *> stk;
    stk.push(root);

    while (!stk.empty()) {
        auto curr = stk.top(); stk.pop();

        for (auto &p: curr->contained_in) {
            Bag *container = p.first;
            if (visited.find(container->get_name()) == visited.end()) {
                visited.insert(container->get_name());
                stk.push(container);
            }
        }
    }

    return visited.size() - 1; // minus one because it contains the target bag itself
}

int main() {
    ifstream ifs("input1.txt");
    string buffer;
    map<string, Bag *> bags;
    while (getline(ifs, buffer)) {
        boost::erase_all(buffer, ".");
        vector<string> split_buffer;
        boost::split_regex(split_buffer, buffer, boost::regex("contain"));

        auto container = split_buffer[0];
        auto contained_string = split_buffer[1];
        boost::erase_all(container, "bags");
        boost::trim(container);

        if (bags.count(container) == 0) {
            Bag *container_bag = new Bag(container);
            bags[container] = container_bag;
        }

        if (boost::contains(contained_string, "no other")) continue;

        vector<string> contained;
        boost::split(contained, contained_string, boost::is_any_of(","));
        for (auto &str: contained) {
            boost::erase_all(str, "bags");
            boost::erase_all(str, "bag");
            boost::trim(str);

            vector<string> split_str;
            boost::split(split_str, str, boost::is_any_of(" "));
            int count = stoi(split_str[0]);
            string contained_name = boost::join(vector<string>(next(split_str.begin()), split_str.end()), " ");
            boost::trim(contained_name);

            if (bags.count(contained_name) == 0) {
                Bag *curr = new Bag(contained_name);
                bags[contained_name] = curr;
            }

            Bag *curr = bags[contained_name];
            Bag *container_bag = bags[container];
            (curr->contained_in).push_back(make_pair(container_bag, count));
        }
    }

    int res = dfs(bags, "shiny gold");
    cout << res << endl;

    // Cleanup
    for (auto it = bags.begin(); it != bags.end(); it++) {
        delete it->second;
    }
}
