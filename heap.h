#include <vector>

class Node {
 public:
  Node() {}
  Node(int key) : key_(key) {}
  int key() { return key_; };
 private:
  int key_;
};

class Heap {
 public:
  static const int MIN_HEAP = -1;
  static const int MAX_HEAP = 1;

  Heap(const int direction = MAX_HEAP) : direction_(direction) {}

  void Push(const Node node) {
    a.push_back(node);
    bubbleUp(a.size() - 1);
  }

  Node Pop() {
    SwapByIndices(0, a.size() - 1);
    Node res = a[a.size() - 1];
    a.pop_back();
    Heapify(0);
    return res;
  }

  bool empty() const {
    return a.empty();
  }

 private:
  int parent(const int i) const { return (i - 1) / 2; }
  int left(const int i) const { return i * 2 + 1; }
  int right (const int i) const { return i * 2 + 2; }

  void SwapByIndices(const int i, const int j) {
    Node temp = a[i];
    a[i] = a[j];
    a[j] = temp;
  }

  bool Compare(const int first, const int second) const {
    return first * direction_ < second * direction_;
  }

  void Heapify(const int i) {
    if (i >= a.size()) return;
    int l = left(i);
    int r = right(i);
    int extreme = i;
    if (l < a.size() && Compare(a[extreme].key(), a[l].key())) extreme = l;
    if (r < a.size() && Compare(a[extreme].key(), a[r].key())) extreme = r;
    if (extreme != i) {
      SwapByIndices(extreme, i);
      Heapify(extreme);
    }
  }

  void bubbleUp(int i) {
    for (; i > 0 && Compare(a[parent(i)].key(), a[i].key()); i = parent(i)) {
      SwapByIndices(parent(i), i);
    }
  }

  const int direction_;
  std::vector<Node> a;
};
