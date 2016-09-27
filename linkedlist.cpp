#include <iostream>
#include "linkedlist.h"


int main() {
  LinkedList list;
  list.Insert(new Item("foo", nullptr));
  list.Insert(new Item("bar", nullptr));
  list.Remove("foo");
  list.Remove("bar");
  return 0;
}
