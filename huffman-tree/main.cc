#include <cassert>
#include "huffman_tree.h"
#include <algorithm>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

string message, cipher;
long double frequency[256];

int main() {
  cout << "\033[1mInput your message to be encoded:\033[0m" << endl;
  getline(cin, message);
  cout << endl << "\033[1mASCII bit:\033[0m" << endl;
  for (auto it: message) {
    cout << bitset<8>(it);
    assert((unsigned char)it >= 0);
    ++frequency[(unsigned char)it];
  }
  cout << endl;
  huffman_tree h(frequency);
  /* encode oringinal message */
  cipher = h.encode(message);
  cout << endl << "\033[1mHuffman encoding bit:\033[0m" << endl;
  cout << cipher << endl;
  /* reserve distinct characters  */
  sort(message.begin(), message.end());
  auto stop = unique(message.begin(), message.end());
  message.resize(distance(message.begin(), stop));
  /* output huffman code for each character */
  cout << endl << "\033[1m freq:  ASCII       Huffman\033[0m" << endl;
  for (auto it: message) {
    cout << it << setw(4) << frequency[(unsigned char)it] << ":  ";
    cout << bitset<8>(it) << "    " << h.encode(it) << endl;
  }
  /* decode huffman code */
  cout << endl << "\033[1mdecoded:\033[0m" << endl;
  cout << h.decode(cipher) << endl;
  return 0;
}

