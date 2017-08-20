#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
 public:
  add_edge(const string& first, const string& second) {
    adjacent_[first].insert(second);
    adjacent_[second].insert(first);
  }

  bool find_shortest_path(const string& source_key,
                          const string& target_key,
                          deque<string>* path) const {
    if (adjacent_.count(source_key) == 0 || adjacent_.count(target_key) == 0) {
      return false;
    }

    unordered_set<string> visited;
    deque<string> queue;
    unordered_map<string, string> backtrace;
    queue.push_back(source_key);
    bool found = false;

    while (!queue.empty()) {
      const string current_key = queue.front();
      if (current_key == target_key) {
        found = true;
        break;
      }
      queue.pop_front();
      visited.insert(current_key);
      for (const string& adjacent_key : adjacent_.find(current_key)->second) {
        if (!visited.count(adjacent_key)) {
          backtrace[adjacent_key] = current_key;
          queue.push_back(adjacent_key);
        }
      }
    }

    if (found && path != nullptr) {
      for (string key = target_key; key != source_key; key = backtrace[key]) {
        path->push_front(key);
      }
      path->push_front(source_key);
    }

    return found;
  }

 private:
  unordered_map<string, unordered_set<string>> adjacent_;
};

void test(const Graph& g, const string& source_key, const string& target_key) {
  cout << "Searching for path; " << source_key << " to " << target_key << endl;
  deque<string> path;
  bool found = g.find_shortest_path(source_key, target_key, &path);

  cout << "found: " << (found ? "yes" : "no") << endl;
  for (const string& key : path) {
    cout << " -> " << key;
  }
  cout << endl << endl;
}


int main() {
  Graph g;
  g.add_edge("a", "b");
  g.add_edge("a", "c");
  g.add_edge("b", "d");
  g.add_edge("c", "e");
  g.add_edge("d", "f");
  g.add_edge("e", "f");

  test(g, "x", "x");
  test(g, "x", "y");
  test(g, "a", "x");
  test(g, "a", "b");
  test(g, "a", "f");
  test(g, "a", "e");
  test(g, "f", "a");
  test(g, "f", "b");
  test(g, "c", "d");
  test(g, "e", "e");

  return 0;
}
