#pragma once

#include <random>
#include <cassert>
#include <climits>
#include <algorithm>

static int random (int l, int r) {
  int len = (r - l + 1);
  assert(len > 0);
  return l + (rand() % len);
}

static std::vector <int> random_array (int n, int l, int r) {
  assert(n > 0);
  std::vector <int> ret_arr(n);
  for (int& elem: ret_arr) elem = random(l, r);
  return ret_arr;
}

static void sort_and_delete_duplicates (std::vector <int>& arr) {
  std::sort(std::begin(arr), std::end(arr));
  arr.erase(std::unique(std::begin(arr), std::end(arr)), std::end(arr));
}

// We are getting the smaller k such that 2 ^ k that is greater than n and 1
// We won't consider overflow cases
// We can actually use bit tricks here to get it in O(1), but let's keep it simple
static int smaller_geq_power2 (int n) {
  int shift = -1;
  for (int bit = 1; bit < 32; bit++) {
    if ((1 << bit) >= n) {
      shift = bit;
      break;
    }
  }
  assert(shift != -1);
  return shift;
}
