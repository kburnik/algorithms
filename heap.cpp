#include <iostream>
#include "heap.h"

using namespace std;

int main() {
  Heap heap(Heap::MAX_HEAP);
  heap.Push(7);
  heap.Push(3);
  heap.Push(81);
  heap.Push(1);
  heap.Push(4);
  heap.Push(2);
  heap.Push(11);
  heap.Push(31);

  while (!heap.empty()) cout << heap.Pop().key() << " ";
  cout << endl;

  return 0;
}

