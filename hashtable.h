#include "linkedlist.h"
#include <iostream>

using namespace std;

class HashTable {
 public:
  HashTable(int size) : size_(size), table_(new LinkedList[size]) {}
  ~HashTable() { delete[] table_; }

   void Insert(Item* item) {
    table_[hash(item->key)].Insert(item);
   }

   Item *Find(const string& key) {
    return table_[hash(key)].Find(key);
   }

   void Describe() {
    for (int i = 0; i < size_ ; ++i) {
      cout << i << ". ";
      table_[i].PrintKeys();
    }
   }
 private:
  int size_;
  LinkedList* table_;

  int hash(const string& key) const {
    int value = 0;
    for (const auto& c : key) value += (int)c;
    return value % size_;
  }
};
