#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "singly_linked_list.h"

string opt;
int value;
bool stop = false;

int main() {
  ios::sync_with_stdio(false);
  cout << boolalpha;
  singly_linked_list<int> ls[2];
  for (int i = 0; i != 2; ++i) {
    int n; cin >> n;
    while (n--) {
      cin >> opt;
      if (opt == "push-front") {
        cin >> value;
        ls[i].push_front(value);
      } else if (opt == "push-back") {
        cin >> value;
        ls[i].push_back(value);
      } else if (opt == "pop-front") {
        ls[i].pop_front();
      } else if (opt == "remove") {
        cin >> value;
        ls[i].remove(value);
      } else if (opt == "incremental-sort") {
        ls[i].sort(increase);
      } else if (opt == "decremental-sort") {
        ls[i].sort(decrease);
      } else if (opt == "reverse") {
        ls[i].reverse();
      } else if (opt == "unique") {
        ls[i].sort(increase);
        ls[i].unique();
      } else stop = false;
      for (auto iter = ls[i].begin(); iter != ls[i].end(); iter += 1)
        cout << *iter << endl;
      cout << endl;
    }
  }
  ls[0].sort(increase); ls[1].sort(increase);
  ls[0].sorted_uniqued_reverse_merge(ls[1]);
  for (auto iter = ls[0].begin(); iter != ls[0].end(); iter += 1)
    cout << *iter << endl;
  cout << endl;
  return 0;
}

