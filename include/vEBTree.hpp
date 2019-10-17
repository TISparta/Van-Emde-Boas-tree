#pragma once

#include "util.hpp"

#include <vector>

static int INF = INT_MAX;
static int NONE = -INF;


class vEBTree {
  private:
    int number_elements;
    int universe_size;
    int k, mask;
    // k, mask are variables for hardware-level optimizations
    // Its meaning is better explained in the constructor and
    // low, high and index functions
    int min, max;
    vEBTree* summary;
    std::vector <vEBTree*> cluster;

    int low (int x) const;
    int high (int x) const;
    int index (int i, int j) const;

    void build ();
    void _insert (int x);
    int _successor (int x) const; 
    int _predecessor (int x) const;
    bool _lookup (int x) const;
    void _erase (int x);

  public:

    vEBTree (int n);
    ~vEBTree ();

    int min_element () const;
    int max_element () const;
    bool is_empty () const;

    void insert (int x);
    bool lookup (int x) const;
    int successor (int x) const; 
    int predecessor (int x) const;
    void erase (int x);
};
