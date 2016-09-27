#include <iostream>
#include "hashtable.h"

using namespace std;

int main() {
  HashTable table(100);

  table.Insert(new Item("foo"));
  table.Insert(new Item("bar"));
  table.Insert(new Item("baz"));
  table.Insert(new Item("rab"));

  cout << table.Find("foo")->key << endl;
  cout << table.Find("bar")->key << endl;
  cout << table.Find("baz")->key << endl;
  cout << table.Find("rab")->key << endl;

  table.Describe();
  return 0;
}
