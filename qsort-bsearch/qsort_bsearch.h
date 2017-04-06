#ifndef _QSORT_BSEARCH_H_
# define _QSORT_BSEARCH_H_

namespace xris {

enum sort_order {
  decrease,
  increase,
};

template <typename elem_t>
void swap(elem_t &l, elem_t &r) {
  elem_t t = l; l = r; r = t;
}

template <typename elem_t>
elem_t max(const elem_t &l, const elem_t &r) {
  return l > r ? l : r;
}

template <typename elem_t>
elem_t min(const elem_t &l, const elem_t &r) {
  return l > r ? r : l;
}

template <typename elem_t>
elem_t middle(const elem_t &l, const elem_t &m, const elem_t &r) {
  elem_t maximum = max(m, max(l, r));
  elem_t minimum = min(m, min(l, r));
  if (minimum < l && l < maximum) return l;
  if (minimum < m && m < maximum) return m;
  if (minimum < r && r < maximum) return r;
}

/**
 * sort an array.
 * average case time complexity:  O(n\log n)
 * average case space complexity: O(\log n)
 * @param s: start point of sorting.
 * @param t: the element right after stop point of sorting.
 * @param order: sort order, increase or decrease, see enum above.
 */
template <typename elem_t>
void quick_sort(elem_t *s, elem_t *t, sort_order o = increase) {
  if (s >= t) return;
  elem_t m = middle(*s, t[-1], s[t - s >> 1]);
  elem_t *l = s, *r = t - 1;
  do {
    while (*l < m == o && *l != m) ++l;
    while (*r > m == o && *r != m) --r;
    if (l <= r) xris::swap(*l++, *r--);
  } while (l <= r);
  quick_sort(s, r + 1, o); quick_sort(l, t, o);
}

/**
 * search an element in a sorted array.
 * time complexity: O(\log n)
 * space complexity: O(1)
 * @param x: the element to be searched.
 * @param s: start point of searching.
 * @param t: stop point of searching.
 * @param o: sort order, same as sort.
 */
template <typename elem_t>
elem_t *binary_search(elem_t x, elem_t *s, elem_t *t, sort_order o) {
  while (s + 1 < t) {
    elem_t *m = s + (t - s >> 1);
    if (x == *m) return m;
    else if (x > *m) s = m + 1;
    else if (x < *m) t = m;
  }
  if (x == *s) return s;
  else return nullptr;
}

}  /* namespace xris */

using xris::sort_order::increase;
using xris::sort_order::decrease;

#endif  /* _QSORT_BSEARCH_H_ */
