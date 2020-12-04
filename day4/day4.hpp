#include <map>

using namespace std;

class Entry {
  public:
    map<string, string> fields;
    bool is_passport();
};

bool Entry::is_passport() {
  auto items = fields.size();
  return items == 8 || (items == 7 && fields.find("cid") == fields.end());
}
