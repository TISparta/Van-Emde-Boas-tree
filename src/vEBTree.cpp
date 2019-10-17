#include "vEBTree.hpp"

#include <stdexcept>

vEBTree::vEBTree (int number_elements): number_elements(number_elements) {
  if (number_elements <= 0) throw std::invalid_argument("Size must be positive");
  k = smaller_geq_power2(number_elements);
  universe_size = (1 << k);
  if (k & 1) { // impar
    k >>= 1; // k /= 2
    k++;
  } else { // par
    k >>= 1; // k /= 2
  }
  mask = (1 << k) - 1; // 2 ^ k - 1
  build();
}

vEBTree::~vEBTree () {
  delete summary;
  for (vEBTree* elem: cluster) delete elem;
  cluster.clear();
}

// x / (2 ^ k)
int vEBTree::high (int x) const { return x >> k; }

// x % (2 ^ k)
int vEBTree::low (int x) const { return x & mask; }

// i * (2 ^ k) + j
int vEBTree::index (int i, int j) const { return (i << k) | j; }

int vEBTree::min_element () const { return min; }

int vEBTree::max_element () const { return max; }

bool vEBTree::is_empty () const { return min == NONE; }

void vEBTree::build () {
  min = max = NONE;
  if (universe_size == 2) {
    summary = nullptr;
    cluster = std::vector <vEBTree*> (0, nullptr);
    return;
  }
  int root_u = (1 << k);
  summary = new vEBTree(root_u);
  cluster = std::vector <vEBTree*> (root_u, nullptr);
  for (int i = 0; i < root_u; i++) {
    cluster[i] = new vEBTree(root_u);
  }
}

void vEBTree::_insert (int x) {
  if (is_empty()) {
    min = max = x;
    return;
  }
  if (x < min) std::swap(x, min);
  if (x > max) max = x;
  if (universe_size == 2) return;
  int i = high(x);
  int j = low(x);
  if (cluster[i] -> min == NONE) summary -> _insert(i);
  cluster[i] -> _insert(j);
}

void vEBTree::insert (int x) {
  if (not (0 <= x and x < number_elements)) {
    throw std::out_of_range("The element if out of range");
  }
  if (lookup(x)) return;
  _insert(x);
}

bool vEBTree::_lookup (int x) const {
  if (min == x or max == x) return true;
  if (universe_size == 2) return false;
  return cluster[high(x)] -> _lookup(low(x));
}

bool vEBTree::lookup (int x) const {
  if (not (0 <= x and x < number_elements)) return false;
  return _lookup(x);
}

int vEBTree::_successor (int x) const {
  if (is_empty()) return NONE;
  if (universe_size == 2 and x == 0 and max == 1) return 1;
  if (universe_size == 2) return NONE;
  if (x < min) return min;
  if (x > max) return NONE;
  int i = high(x);
  int j = low(x);
  if (j < cluster[i] -> max) {
    j = cluster[i] -> _successor(j);
  } else {
    i = summary -> _successor(i);
    if (i == NONE) return NONE;
    j = cluster[i] -> min;
  }
  return index(i, j);
}

int vEBTree::successor (int x) const {
  if (x >= number_elements) return NONE;
  if (x < 0) return min;
  return _successor(x);
}

int vEBTree::_predecessor (int x) const {
  if (is_empty()) return NONE;
  if (universe_size == 2 and x == 1 and min == 0) return 0;
  if (universe_size == 2) return NONE;
  if (max < x) return max;
  if (x < min) return NONE;
  int i = high(x);
  int j = low(x);
  if (cluster[i] -> min != NONE and cluster[i] -> min < j) {
    j = cluster[i] -> _predecessor(j);
  } else {
    i = summary -> _predecessor(i);
    if (i == NONE and min < x) return min;
    if (i == NONE) return NONE;
    j = cluster[i] -> max;
  }
  return index(i, j);
}

int vEBTree::predecessor (int x) const {
  if (x >= number_elements) return max;
  if (x < 0) return NONE;
  return _predecessor(x);
}

void vEBTree::_erase (int x) {
  if (min == x and max == x) {
    min = max = NONE;
    return;
  }
  if (universe_size == 2) {
    if (x == 0) min = 1;
    if (x == 1) min = 0;
    max = min;
    return;
  }
  if (x == min) {
    int cur = summary -> min;
    if (cur == NONE) {
      min = max = NONE;
      return;
    }
    x = min = index(cur, cluster[cur] -> min);
  }
  int i = high(x);
  int j = low(x);
  cluster[i] -> _erase(j);
  if (cluster[i] -> min == NONE) {
    summary -> _erase(i);
  }
  if (x == max) {
    if (summary -> max == NONE) {
      max = min;
    } else {
      int cur = summary -> max;
      max = index(cur, cluster[cur] -> max);
    }
  }
}

void vEBTree::erase (int x) {
  if (not lookup(x)) return;
  _erase(x);
}
