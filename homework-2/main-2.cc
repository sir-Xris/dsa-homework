#include "huffman_tree.h"
#include <iostream>
#include <iomanip>
using namespace std;

int freq[256];

int main() {
  freq['A'] = 7;  freq['B'] = 9;  freq['C'] = 12;
  freq['D'] = 22; freq['E'] = 23; freq['F'] = 27;

  ios::sync_with_stdio(false);
  huffman_tree coder(freq);
  for (char i = 'A'; i <= 'F'; ++i) {
    cout << i << ": " << coder.encode(i) << endl;
  }
  return 0;
}
