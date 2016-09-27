#include <iostream>

using namespace std;

class Item {
 public:
  Item(string item_key, Item* next_item = nullptr)
      : key(item_key), next(next_item) {}
  string key;
  Item* next;
};

class LinkedList {
 public:
  LinkedList() : head(nullptr) {}
  ~LinkedList() {
    for (Item *p = head; p != nullptr; ) {
      Item *item = p;
      p = p->next;
      delete item;
    }
  }

  void Insert(Item* item) {
    item->next = head;
    head = item;
  }

  Item* Find(const string& key) {
    for (Item* p = head; p != nullptr; p = p->next) {
      if (p->key == key) return p;
    }
    return nullptr;
  }

  bool Remove(const string& key) {
    Item prehead("", head);
    for (Item* p = &prehead; p->next != nullptr; p = p->next) {
      if (p->next->key == key) {
        Item* match = p->next;
        p->next = match->next;
        delete match;
        return true;
      }
    }
    return false;
  }

  void PrintKeys() {
    for (Item *p = head; p != nullptr; p = p->next)
      cout << p->key << " ";
    cout << endl;
  }
 private:
  Item* head;
};
