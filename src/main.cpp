#include "vEBTree.hpp"
#include "util.hpp"

#include <iostream>
#include <iomanip>
#include <set>

const int INSERT = 0;
const int LOOKUP = 1;
const int PREDECESSOR = 2;
const int SUCCESSOR = 3;
const int ERASE = 4;
const int N_OPERATIONS = 5;
const int TIMES = 100;
const int N_QUERIES = 1e6;

void how_to_use_it () {
  std::cout << "Usage: ./comparison <size_vEBTree>" << std::endl;
  exit(0);
}

void insert_vEBTree (vEBTree& tree, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) tree.insert(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void insert_set (std::set <int>& st, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) st.insert(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void lookup_vEBTree (vEBTree& tree, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) tree.lookup(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void lookup_set (std::set <int>& st, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) st.find(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void predecessor_vEBTree (vEBTree& tree, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) tree.predecessor(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void predecessor_set (std::set <int>& set, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) {
    auto it = set.lower_bound(elem);
    if (it != std::begin(set)) it--;
  }
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void successor_vEBTree (vEBTree& tree, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) tree.successor(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void successor_set (std::set <int>& set, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) set.upper_bound(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void erase_vEBTree (vEBTree& tree, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) tree.erase(elem);
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void erase_set (std::set <int>& set, const std::vector <int>& elements, std::vector <double>& time) {
  clock_t start, end;
  start = clock();
  for (int elem: elements) {
    auto it = set.find(elem);
    if (it != std::end(set)) set.erase(it);
  }
  end = clock();
  time.push_back(1.0 * (end - start) / CLOCKS_PER_SEC);
}

void add (const std::string& label, double time_vEBTree, double time_set) {
  std::cout << std::fixed << std::setprecision(6) <<
    " | " << label << " | " << time_vEBTree << " | " << time_set << " |  " << std::endl;
}

double average (const std::vector <double>& time) {
  return std::accumulate(std::begin(time), std::end(time), 0.0) / double(time.size());
}

void print_markdown_table (std::vector <std::vector <double>> time_vEBTree,
                           std::vector <std::vector <double>> time_set) {
  std::cout << "| Operation | vEB Tree | Set |  " << std::endl;
  std::cout << "| ----- --- | -------- | --- |  " << std::endl;
  add("INSERT", average(time_vEBTree[INSERT]), average(time_set[INSERT]));
  add("LOOKUP", average(time_vEBTree[LOOKUP]), average(time_set[LOOKUP]));
  add("PREDECESSOR", average(time_vEBTree[PREDECESSOR]), average(time_set[PREDECESSOR]));
  add("SUCCESSOR", average(time_vEBTree[SUCCESSOR]), average(time_set[SUCCESSOR]));
  add("ERASE", average(time_vEBTree[ERASE]), average(time_set[ERASE]));
}

int main (int argc, char** argv) {
  if (argc != 2) how_to_use_it();
  int n = atoi(argv[1]);
  std::vector <std::vector <double>> time_vEBTree(N_OPERATIONS);
  std::vector <std::vector <double>> time_set(N_OPERATIONS);
  for (int t = 0; t < TIMES; t++) {
    std::vector <int> to_insert = random_array(N_QUERIES, 0, n - 1);
    std::vector <int> random_numbers = random_array(N_QUERIES, 0, n - 1);
    vEBTree tree(n);
    std::set <int> set;

    insert_vEBTree(tree, to_insert, time_vEBTree[INSERT]);
    insert_set(set, to_insert, time_set[INSERT]);

    lookup_vEBTree(tree, random_numbers, time_vEBTree[LOOKUP]);
    lookup_set(set, random_numbers, time_set[LOOKUP]);

    predecessor_vEBTree(tree, random_numbers, time_vEBTree[PREDECESSOR]);
    predecessor_set(set, random_numbers, time_set[PREDECESSOR]);

    successor_vEBTree(tree, random_numbers, time_vEBTree[SUCCESSOR]);
    successor_set(set, random_numbers, time_set[SUCCESSOR]);

    erase_vEBTree(tree, random_numbers, time_vEBTree[ERASE]);
    erase_set(set, random_numbers, time_set[ERASE]);
  }
  print_markdown_table(time_vEBTree, time_set);
  return (0);
}
