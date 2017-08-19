// A simple Trie implementation.
// This was an exercise for coding interviews.
// It's not necessarily the cleanest solution, but it demonstrates the concept.
// I'm using C++11 so specify the --std=c++11 flag with g++.

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// A dictionary-like data structure for storing strings. It allows lookups on
// strings or prefixes. An example use case would be an autocomplete/suggest
// feature (e.g. search by prefix).
class Trie {
 private:
  // Represents the structure of a single trie node.
  struct Node {
    map<char, Node> children;
    bool terminal = false;
  };

 public:
  // Inserts a string into the trie.
  void insert(const string& s) {
    Node* node = &root;
    for (const char c : s) {
      node = &node->children[c];
    }
    node->terminal = true;
  }

  // Finds all strings with given prefix and pushes them to the out vector.
  void find(const string& prefix, vector<string>* out) const {
    traverse(
        find_node(prefix),
        prefix,
        [&](const string& s) { out->push_back(s); });
  }

  // Determines if there's a string with given prefix in the trie.
  bool has_prefix(const string& prefix) const {
    return find_node(prefix) != nullptr;
  }

  // Determines whether a string exists in the trie.
  bool has_string(const string& prefix) const {
    Node* node = find_node(prefix);
    return node != nullptr && node->terminal;
  }

  // Returns the number of strings with a given prefix.
  int count(const string& prefix) const {
    int count = 0;
    traverse(
        find_node(prefix),
        prefix,
        [&](const string& s) { count++; });
    return count;
  }

  // Displays the trie structure for debugging.
  void debug() const {
    cout << "<Root node>" << (root.terminal ? " *": "") << endl;
    debug_output(&root, 1, "");
  }

 private:
  // Recursively prints the trie for debugging.
  void debug_output(const Node* node, int level, const string& prefix) const {
    for (const auto kvp : node->children) {
      cout << string(level, ' ') << prefix << kvp.first;
      if (kvp.second.terminal) cout << " *";
      cout << endl;
      debug_output(&kvp.second, level + 1, prefix + string(1, kvp.first));
    }
  }

  // Finds and returns the node for the given prefix in the trie. If the prefix
  // does not exist, returns a null pointer.
  Node* find_node(const string& prefix) const {
    Node* node = const_cast<Node*>(&root);
    for (const char c : prefix) {
      if (!node->children.count(c)) {
        return nullptr;
      }
      node = &node->children[c];
    }
    return node;
  }

  // Recursively traverses each node of the trie starting from the provided
  // node. If the node is a terminal, runs the callback with the entire string.
  void traverse(
      const Node* node,
      const string& prefix,
      function<void(const string&)> callback) const {
    if (node == nullptr) {
      return;
    }
    if (node->terminal) {
      callback(prefix);
    }
    for (const auto kvp : node->children) {
      traverse(&kvp.second, prefix + string(1, kvp.first), callback);
    }
  }

  // The trie only needs a reference to the root node.
  Node root;
};

int main() {
  Trie t;
  t.insert("abc");
  t.insert("abcd");
  t.insert("abcg");
  t.insert("klm");
  t.insert("klo");
  t.insert("kgh");

  cout << "Tree preview" << endl;
  t.debug();
  cout << endl;

  cout << "Has prefix: ab --> " << (t.has_prefix("ab") ? "yes" : "no") << endl;
  cout << "Has word: ab --> " << (t.has_string("ab") ? "yes" : "no") << endl;
  cout << "Has word: abc --> " << (t.has_string("abc") ? "yes" : "no") << endl;
  cout << "Has word: abcd --> " << (t.has_string("abcd") ? "yes" : "no")
      << endl;
  cout << "No. of words with prefix: ab --> " << t.count("ab") << endl;
  cout << "No. of words with prefix: <none> --> " << t.count("") << endl;

  cout << endl;

  vector<string> words;
  cout << "Find words with prefix: k" << endl;
  t.find("k", &words);
  for (auto s : words) {
    cout << s << endl;
  }

  return 0;
}
