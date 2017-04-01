/**
 * Iterators for singly_linked_list.
 * I did not want to implement this originally,
 * but my teacher said "Why not?".
 * Well so I just simply try it.
 * Never used in this project.
 */

#ifdef _SINGLY_LINKED_LIST_H_

template <typename elem_t>
class singly_linked_list<elem_t>::iterator {
 private:
  node *pointer;
 public:
  iterator(node *);
  ~iterator() {};
  iterator &operator++();
  iterator operator++(int);
  iterator &operator+=(size_t);
  iterator operator+(size_t);
  bool operator==(const iterator &) const;
  bool operator!=(const iterator &) const;
  elem_t &operator*() const;
};

template <typename elem_t>
singly_linked_list<elem_t>::iterator::iterator(node *p) {
  this->pointer = p;
}

template <typename elem_t>
typename singly_linked_list<elem_t>::iterator &
singly_linked_list<elem_t>::iterator::operator++() {
  this->pointer = this->pointer->next;
  return *this;
}

template <typename elem_t>
typename singly_linked_list<elem_t>::iterator
singly_linked_list<elem_t>::iterator::operator++(int) {
  auto ret = *this;
  this->pointer = this->pointer->next;
  return ret;
}

template <typename elem_t>
typename singly_linked_list<elem_t>::iterator &
singly_linked_list<elem_t>::iterator::operator+=(size_t n) {
  while (n--) this->pointer = this->pointer->next;
  return *this;
}

template <typename elem_t>
typename singly_linked_list<elem_t>::iterator
singly_linked_list<elem_t>::iterator::operator+(size_t n) {
  singly_linked_list<elem_t>::iterator iter = this;
  while (n--) iter->pointer = iter->pointer->next;
  return iter;
}

template <typename elem_t>
bool singly_linked_list<elem_t>::iterator::operator==(
    const singly_linked_list<elem_t>::iterator &it) const {
  return this->pointer == it.pointer;
}

template <typename elem_t>
bool singly_linked_list<elem_t>::iterator::operator!=(
    const singly_linked_list<elem_t>::iterator &it) const {
  return this->pointer != it.pointer;
}

template <typename elem_t>
elem_t &singly_linked_list<elem_t>::iterator::operator*() const {
  return this->pointer->data;
}

#endif  /* _SINGLY_LINKED_LIST_H_ */
