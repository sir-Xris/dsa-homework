#include <random>
#include <iostream>
#include <iomanip>
using namespace std;

random_device seed;
uniform_int_distribution<long long> unif(0, ~0ull >> 1);

string opt[] = {
  "push-back",
//  "remove",
//  "incremental-sort",
//  "decremental-sort",
//  "reverse",
//  "unique",
};

int main() {
  ios::sync_with_stdio(false);
  for (int i = 0; i != 2; ++i) {
    int n = 10000;
    cout << n << endl;
    while (n--) {
      int option = unif(seed) % (sizeof opt / sizeof *opt);
      cout << opt[option] << ' ';
      if (option < 2) {
        cout << (unif(seed) & 0x7) << endl;
      } else cout << endl;
    }
  }
  return 0;
}
