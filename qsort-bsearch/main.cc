#include "qsort_bsearch.h"
#include <iostream>
using namespace std;

int a[1024];
int n, m;

int main() {
  cin >> n >> m;
  for (int i = 0; i != n; ++i)
    cin >> a[i];
  cout << "read done" << endl;
  xris::quick_sort(a, a + n, increase);
  for (int i = 0; i != n; ++i)
    cout << a[i] << endl;
  while (m--) {
    int x; cin >> x;
    int *p = xris::binary_search(x, a, a + n, increase);
    if (p) {
      cout << p - a << endl;
    } else cout << "not found" << endl;
  }
  return 0;
}

