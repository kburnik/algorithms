#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <class T> class Graph {
 public:
  add_edge(const T& first, const T& second) {
    adjacent_[first].insert(second);
    adjacent_[second].insert(first);
  }

  bool find_shortest_path(const T& source,
                          const T& target,
                          deque<T>* path) const {
    if (adjacent_.count(source) == 0 || adjacent_.count(target) == 0) {
      return false;
    }

    unordered_set<T> visited;
    deque<T> queue;
    unordered_map<T, T> backtrace;
    queue.push_back(source);
    bool found = false;

    while (!queue.empty()) {
      const T current = queue.front();
      if (current == target) {
        found = true;
        break;
      }
      queue.pop_front();
      visited.insert(current);
      for (const T& adjacent : adjacent_.find(current)->second) {
        if (!visited.count(adjacent)) {
          backtrace[adjacent] = current;
          queue.push_back(adjacent);
        }
      }
    }

    if (found && path != nullptr) {
      for (T node = target; node != source; node = backtrace[node]) {
        path->push_front(node);
      }
      path->push_front(source);
    }

    return found;
  }

 private:
  unordered_map<T, unordered_set<T>> adjacent_;
};

void test(const Graph<string>& g, const string& source, const string& target) {
  cout << "Searching for path: " << source << " to " << target << endl;
  deque<string> path;
  bool found = g.find_shortest_path(source, target, &path);

  cout << "found: " << (found ? "yes" : "no") << endl;
  for (const string& node : path) {
    cout << " -> " << node;
  }
  cout << endl << endl;
}

int main() {
  Graph<string> g;
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
