#include "vEBTree.hpp"
#include "util.hpp"

#include <gtest/gtest.h>

const int TIMES = 10;
const int MAX = 1 << 16;
const int MAX_CNT = 1e3;

TEST(vEBTree, build) {
  for (int t = 0; t < TIMES; t++) {
    vEBTree tree(random(1, MAX));
  }
}

TEST(vEBTree, build_non_positive_size) {
  ASSERT_THROW(vEBTree(0), std::invalid_argument);
  ASSERT_THROW(vEBTree(random(-MAX, -1)), std::invalid_argument);
}

TEST(vEBTree, lookup) {
  for (int t = 0; t < TIMES; t++) {
    int n = random(1, MAX);
    vEBTree tree(n);
    int m = random(1, MAX_CNT);
    std::vector <int> to_insert = random_array(m, 0, n - 1);
    for (int elem: to_insert) {
      tree.insert(elem);
      EXPECT_TRUE(tree.lookup(elem));
    }
  }
}

TEST(vEBTree, lookup_out_of_range) {
  for (int t = 0; t < TIMES; t++) {
    int n = random(1, MAX);
    vEBTree tree(n);
    EXPECT_FALSE(tree.lookup(random(-n, -1)));
    EXPECT_FALSE(tree.lookup(random(n, 2 * n)));
  }
}

TEST(vEBTree, insert) {
  for (int t = 0; t < TIMES; t++) {
    int n = random(1, MAX);
    vEBTree tree(n);
    int m = random(1, MAX_CNT);
    std::vector <int> to_insert = random_array(m, 0, n - 1);
    for (int elem: to_insert) {
      tree.insert(elem);
      ASSERT_TRUE(tree.lookup(elem));
    }
    // Inserting again
    for (int elem: to_insert) {
      tree.insert(elem);
      ASSERT_TRUE(tree.lookup(elem));
    }
  }
}

TEST(vEBTree, insert_out_of_range) {
  for (int t = 0; t < TIMES; t++) {
    int n = random(1, MAX);
    vEBTree tree(n);
    ASSERT_THROW(tree.insert(random(-n, -1)), std::out_of_range);
    n = std::max(2, n);
    ASSERT_THROW(tree.insert(random(n, 2 * n)), std::out_of_range);
  }
}

TEST(vEBTree, is_empty) {
  int n = random(1, MAX);
  vEBTree tree(n);
  ASSERT_TRUE(tree.is_empty());
  tree.insert(0);
  ASSERT_FALSE(tree.is_empty());
  tree.erase(0);
  ASSERT_TRUE(tree.is_empty());
}

TEST(vEBTree, min_element) {
  for (int t = 0; t < TIMES; t++) { 
    int n = random(1, MAX);
    vEBTree tree(n);
    int m = random(1, MAX_CNT);
    std::vector <int> to_insert = random_array(m, 0, n - 1);
    int min = INF;
    for (int elem: to_insert) {
      min = std::min(min, elem);
      tree.insert(elem);
      ASSERT_TRUE(tree.min_element() == min);
    }
    sort_and_delete_duplicates(to_insert);
    for (int elem: to_insert) {
      ASSERT_TRUE(tree.min_element() == elem);
      tree.erase(elem);
    }
    ASSERT_TRUE(tree.is_empty());
  }
}

TEST(vEBTree, max_element) {
  for (int t = 0; t < TIMES; t++) { 
    int n = random(1, MAX);
    vEBTree tree(n);
    int m = random(1, MAX_CNT);
    std::vector <int> to_insert = random_array(m, 0, n - 1);
    int max = -INF;
    for (int elem: to_insert) {
      max = std::max(max, elem);
      tree.insert(elem);
      ASSERT_TRUE(tree.max_element() == max);
    }
    sort_and_delete_duplicates(to_insert);
    std::reverse(std::begin(to_insert), std::end(to_insert));
    for (int elem: to_insert) {
      ASSERT_TRUE(tree.max_element() == elem);
      tree.erase(elem);
    }
    ASSERT_TRUE(tree.is_empty());
  }
}

TEST(vEBTree, successor) {
  for (int t = 0; t < TIMES; t++) {
    int n = random(1, MAX);
    vEBTree tree(n);
    int m = random(1, MAX_CNT);
    std::vector <int> to_insert = random_array(m, 0, n - 1);
    for (int i = 0; i < m; i++) {
      tree.insert(to_insert[i]);
      int successor = NONE;
      for (int j = i; j >= 0; j--) {
        if (to_insert[j] > to_insert[i]) {
          if (successor == NONE) successor = to_insert[j];
          successor = std::min(successor, to_insert[j]);
        }
      }
      ASSERT_TRUE(tree.successor(to_insert[i]) == successor);
    }
  }
}

TEST(vEBTree, predecessor) {
  for (int t = 0; t < TIMES; t++) {
    int n = random(1, MAX);
    vEBTree tree(n);
    int m = random(1, MAX_CNT);
    std::vector <int> to_insert = random_array(m, 0, n - 1);
    for (int i = 0; i < m; i++) {
      tree.insert(to_insert[i]);
      int predecessor = NONE;
      for (int j = i; j >= 0; j--) {
        if (to_insert[j] < to_insert[i]) {
          if (predecessor == NONE) predecessor = to_insert[j];
          predecessor = std::max(predecessor, to_insert[j]);
        }
      }
      ASSERT_TRUE(tree.predecessor(to_insert[i]) == predecessor);
    }
  }
}

TEST(vEBTree, erase) {
  for (int t = 0; t < TIMES; t++) {
    int n = random(1, MAX);
    vEBTree tree(n);
    int m = random(1, MAX_CNT);
    std::vector <int> to_insert = random_array(m, 0, n - 1);
    sort_and_delete_duplicates(to_insert);
    std::reverse(std::begin(to_insert), std::end(to_insert));
    for (int elem: to_insert) {
      tree.insert(elem);
    }
    for (int elem: to_insert) {
      ASSERT_TRUE(tree.lookup(elem));
      tree.erase(elem);
      ASSERT_FALSE(tree.lookup(elem));
    }
  }
}

int main (int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
