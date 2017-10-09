#include <iostream>
#include "for.h"

using namespace std;

template <int n>
struct TreeSum {
    TreeSum<n - 1> c;
    int t = n + c.t;
};

template <>
struct TreeSum<0> {
    int t = 0;
};
