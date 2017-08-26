#include <iostream>
#include "for.h"

using namespace std;

template <int n, typename T>
struct Cons {
    Cons<n - 1, T> c;
    T t;
};

template <typename T>
struct Cons<0, T> {
    T t;
};

int main () {
    Cons<6, int> c;
    c.t = 6;
    c.c.t = 5;
    c.c.c.t = 2;
    cout << c.c.t << endl;
}
