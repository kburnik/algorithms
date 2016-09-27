#include <iostream>
#include <map>

using namespace std;

int find_max_length(const string& s, const int k) {
  if (k <= 0 || s.size() == 0) return 0;
  int max_length = 0;
  int left = 0, right = 0;
  map<char, int> hist;
  while (right < s.size()) {
    hist[s[right]]++;
    while (hist.size() > k) {
      if (--hist[s[left]] == 0) hist.erase(s[left]);
      left++;
    }
    int new_length = right - left + 1;
    if (new_length > max_length) max_length = new_length;
    right++;
  }
  return max_length;
}

int main() {
  int k;
  string s;
  cin >> k >> s;
  cout << "Max length = " << find_max_length(s, k) << endl;
  return 0;
}
