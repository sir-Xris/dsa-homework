/**
 * Huffman Tree, Huffman Coding.
 * 2016220204004 信息与软件工程学院 软件工程（软件技术） 叶鉴赏
 */
#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_ 1

#include <cfloat>     // FLT_EPSILON
#include <cmath>      // std::abs
#include <queue>      // std::priority_queue
#include <stdexcept>  // std::invalie_argument
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * Only support encoding for ASCII characters.
 */
class huffman_tree {
 private:
  struct node {
    char character;
    long double frequency;
    node *lchild, *rchild;
  } *root;
  std::string coding[256];
  void extract_coding(node *);

 public:
  template <typename T>
  huffman_tree(const T [256]);
  std::string encode(std::string) const;
  std::string encode(char) const;
  std::string decode(std::string) const;
  friend struct _freq_cmp;
};

struct _freq_cmp {
  bool operator()(huffman_tree::node *l, huffman_tree::node *r) {
    return l->frequency > r->frequency;
  }
};

/**
 * constructor.
 * param @frequecy: The frequencies of all ASCII characters in an array.
 */
template <typename T>
huffman_tree::huffman_tree(const T frequency[256]) {
  std::priority_queue<node *, std::vector<node *>, _freq_cmp> forest;
  for (int i = 0; i != 256; ++i)
    if (std::abs(frequency[i]) > FLT_EPSILON)
      forest.push(new node{char(i), frequency[i], nullptr, nullptr});
  while (forest.size() > 1) {
    node *min1 = forest.top(); forest.pop();
    node *min2 = forest.top(); forest.pop();
    forest.push(new node{-1, min1->frequency + min2->frequency, min1, min2});
  }
  this->root = forest.top(); forest.pop();
  this->extract_coding(this->root);
}

std::string _temp_extract;
void huffman_tree::extract_coding(huffman_tree::node *n) {
  if (n->lchild != nullptr) {
    _temp_extract.push_back('0');
    this->extract_coding(n->lchild);
    _temp_extract.pop_back();
  }
  if (n->character != -1)
    this->coding[n->character] = _temp_extract;
  if (n->rchild != nullptr) {
    _temp_extract.push_back('1');
    this->extract_coding(n->rchild);
    _temp_extract.pop_back();
  }
}

std::string huffman_tree::encode(std::string message) const {
  std::string cipher;
  for (auto it: message) {
    cipher += this->coding[it];
  }
  return cipher;
}

std::string huffman_tree::encode(char message) const {
  return this->coding[message];
}

std::string huffman_tree::decode(std::string cipher) const {
  std::string message;
  huffman_tree::node *p = this->root;
  for (auto it: cipher) {
    switch (it) {
      case '0':
        if (p->lchild == nullptr) {
          throw std::invalid_argument("cannot decode this cipher");
        }
        p = p->lchild; 
        break;
      case '1':
        if (p->rchild == nullptr) {
          throw std::invalid_argument("cannot decode this cipher");
        }
        p = p->rchild; 
        break;
      default:
        throw std::invalid_argument("cipher have to be `0' or `1'");
        break;
    }
    if (p->character != -1) {
      message.push_back(p->character);
      p = this->root;
    }
  }
  return message;
}

#endif  /* _HUFFMAN_TREE_H_ */

