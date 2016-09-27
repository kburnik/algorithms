#include <iostream>
#include <functional>
#include <vector>

using namespace std;

void selectionsort(int a[], int lo, int hi) {
  for (int i = lo; i <= hi - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j <= hi; j++) {
      if (a[j] < a[minIndex]) minIndex = j;
    }
    swap(a[minIndex], a[i]);
  }
}

void bubblesort(int a[], int lo, int hi) {
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (int i = lo; i <= hi; i++) {
      if (a[i] > a[i+1]) {
        swap(a[i], a[i+1]);
        sorted = false;
      }
    }
    hi--;
  }
}

// insertion sort
// heap sort

void quicksort(int a[], int lo, int hi) {
  if (lo >= hi) return;
  int pivot = a[(lo + hi) / 2];
  int i = lo;
  int j = hi;
  while (i <= j) {
    while (a[i] < pivot) i++;
    while (a[j] > pivot) j--;
    if (i <= j) {
      swap(a[i], a[j]);
      i++;
      j--;
    }
  }
  quicksort(a, lo, j);
  quicksort(a, i, hi);
}

void merge(int a[], int lo, int mid, int hi) {
  int t[hi - lo + 1];
  int i = lo, j = mid + 1, k = 0;
  while (i <= mid && j <= hi) t[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
  while (i <= mid) t[k++] = a[i++];
  while (j <= hi) t[k++] = a[j++];
  for (int p = lo; p <= hi; p++) a[p] = t[p - lo];
}

void mergesort(int a[], int lo, int hi) {
  if (lo >= hi) return;
  int mid = (lo + hi) / 2;
  mergesort(a, lo, mid);
  mergesort(a, mid + 1, hi);
  merge(a, lo, mid, hi);
}

void radixsort(int a[], int lo, int hi) {
  const int radix = 10;
  bool sorted = false;
  int d = 1;
  while (!sorted) {
    sorted = true;
    vector<vector<int>> buckets(radix);
    for (int i = lo; i <= hi; i++) {
      int digit = (a[i] / d) % radix;
      buckets[digit].push_back(a[i]);
      if (digit > 0) sorted = false;
    }

    int i = lo;
    for (int j = 0; j < buckets.size(); j++) {
      for (int k = 0; k < buckets[j].size(); k++) {
        a[i++] = buckets[j][k];
      }
    }

    d *= radix;
  }
}

void sort(const string& name, std::function<void(int[], int, int)> algo) {
  int a[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int size = sizeof(a) / sizeof(int);

  cout << name << endl;

  for (int i = 0; i < size; ++i) cout << a[i] << " ";
  cout  << endl;

  algo(a, 0, size-1);

  for (int i = 0; i < size; ++i) cout << a[i] << " ";
  cout << endl << "----" << endl;
}

int main() {
  sort("Selection", selectionsort);
  sort("Bubble", bubblesort);
  sort("Quick", quicksort);
  sort("Merge", mergesort);
  sort("Radix", radixsort);

  return 0;
}
