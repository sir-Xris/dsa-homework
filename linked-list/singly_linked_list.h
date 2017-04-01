/**
 * Simulation of std::forward_list in STL, but somehow different.
 * Implemented some functions, iterator. Too busy to fully implement STL.
 */
#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_ 1

#include <ostream>  /* std::ostream */

enum sort_order { decrease, increase };

template <typename elem_t>
class singly_linked_list {
 private:
  struct node {
    elem_t data;
    node *next;
  } *head, *tail;

  void _quick_sort(node *, node *, sort_order);

 public:

  class iterator;
  /* constructor and destructor */
  singly_linked_list();
  ~singly_linked_list();

  /* overload operator<< with std::ostream */
  template <typename _elem_t>
  friend std::ostream &operator<<(
    std::ostream &,
    const singly_linked_list<_elem_t> &
  );

  /* insert */
  void push_front(const elem_t &);
  void push_back(const elem_t &);

  /* delete */
  void pop_front();
  void remove(const elem_t &);

  /* utilities */
  void sort(const sort_order);
  void reverse();
  void unique();
  /**
   * this is homework!
   * name of the function makes me lol.
   */
  void sorted_uniqued_reverse_merge(const singly_linked_list<elem_t> &);
  
  iterator begin();
  iterator end();
};

template <typename elem_t>
singly_linked_list<elem_t>::singly_linked_list() {
  this->head = this->tail = nullptr;
}

template <typename elem_t>
singly_linked_list<elem_t>::~singly_linked_list() {
  if (this->head == nullptr) return;
  for (node *p = this->head; p != nullptr;) {
    node *q = p->next; delete p; p = q;
  }
}

template <typename elem_t>
std::ostream &operator<<(
    std::ostream &os,
    const singly_linked_list<elem_t> &ls) {
  for (auto p = ls.head; p != nullptr; p = p->next) {
    os << p->data << std::endl;
  }
  return os;
}

template <typename elem_t>
void singly_linked_list<elem_t>::push_front(const elem_t &val) {
  node *p = new node{val, this->head};
  if (this->head == nullptr) {
    this->tail = p;
  }
  this->head = p;
}

template <typename elem_t>
void singly_linked_list<elem_t>::push_back(const elem_t &val) {
  node *p = new node{val, nullptr};
  if (this->tail == nullptr) {
    this->head = p;
  } else {
    this->tail->next = p;
  }
  this->tail = p;
}

template <typename elem_t>
void singly_linked_list<elem_t>::pop_front() {
  /**
   * Here if the list is empty, std::forward_list will cause an segment fault.
   * This means that it is the programmer's responsibility to check whether
   * the linked list is empty or not.
   */
  node *p = this->head;
  this->head = p->next;
  if (p->next == nullptr) {
    this->tail = nullptr;
  }
  delete p;
}

template <typename elem_t>
void singly_linked_list<elem_t>::remove(const elem_t &val) {
  /**
   * Find the first node with data not equals to val.
   */
  while (this->head != nullptr) {
    if (this->head->data == val) {
      node *p = this->head->next;
      delete this->head;
      this->head = p;
    } else break;
  }
  /**
   * May be all nodes have val's data,
   * or the list is empty originally.
   */
  if (this->head == nullptr) {
    this->tail = nullptr;
    return;
  }
  for (node *p = this->head; p->next != nullptr;) {
    node *q = p->next;
    if (q->data == val) {
      p->next = q->next;
      if (q == this->tail) {
        this->tail = p;
      }
      delete q;
    } else p = p->next;
  }
}

/**
 * call _quick_sort
 */
template <typename elem_t>
void singly_linked_list<elem_t>::sort(const sort_order ord) {
  if (this->head == nullptr || this->head == this->tail) return;
  this->_quick_sort(this->head, nullptr, ord);
}

/**
 * quick sort
 * time complexity: O(n\log n)
 * space complexity: O(1)
 */
template <typename elem_t>
void singly_linked_list<elem_t>::_quick_sort(
    node *s,
    node *t,
    sort_order ord) {
  if (s == t) return;
  node *p = s; elem_t key = s->data;
  for (node *q = p->next; q != t; q = q->next) {
    if ((q->data < key) == ord) {
      p = p->next;
      elem_t tmp = p->data;
      p->data = q->data;
      q->data = tmp;
    }
  }
  elem_t tmp = p->data;
  p->data = s->data;
  s->data = tmp;
  this->_quick_sort(s, p, ord);
  this->_quick_sort(p->next, t, ord);
}

template <typename elem_t>
void singly_linked_list<elem_t>::reverse() {
  if (this->head == nullptr) return;
  node *front = this->head;
  while (front->next != nullptr) {
    node *p = front->next;
    front->next = p->next;
    p->next = this->head;
    this->head = p;
  }
  this->tail = front;
}

/**
 * Remove *consecutive* duplicated elements.
 */
template <typename elem_t>
void singly_linked_list<elem_t>::unique() {
  for (auto p = this->head; p != nullptr; p = p->next) {
    auto q = p->next;
    while (q != nullptr && p->data == q->data) {
      p->next = q->next;
      if (q == this->tail) {
        this->tail = p;
      }
      delete q;
      q = p->next;
    }
  }
}

/**
 * User has to ensure both lists are incremental.
 * Homework requirement.
 * Strategy: ordered insert list into `this', then reverse, finally unique.
 * 哇，一个函数这么多功能，容许我用一下中文来吐槽（函数名）。
 */
template <typename elem_t>
void singly_linked_list<elem_t>::sorted_uniqued_reverse_merge(
    const singly_linked_list<elem_t> &ls) {
  node *q = ls.head;
  /* If `this' is empty */
  if (this->head == nullptr) {
    while (q != nullptr) {
      this->push_back(q->data);
      q = q->next;
    }
  }
  if (q != nullptr && q->data <= this->head->data) {
    this->head = new node{q->data, this->head};
    q = q->next;
  }
  node *p = this->head;
  while (p != nullptr && q != nullptr) {
    if (p->next == nullptr || q->data <= p->next->data) {
      p->next = new node{q->data, p->next};
      q = q->next;
    }
    p = p->next;
  }
  this->unique();
  this->reverse();
}

#include "singly_linked_list_iter.h"

template <typename elem_t>
typename singly_linked_list<elem_t>::iterator
singly_linked_list<elem_t>::begin() {
  return singly_linked_list<elem_t>::iterator{this->head};
}

template <typename elem_t>
typename singly_linked_list<elem_t>::iterator
singly_linked_list<elem_t>::end() {
  return singly_linked_list<elem_t>::iterator{nullptr};
}

#endif  /* _SINGULAR_LINKED_LIST_H_ */

