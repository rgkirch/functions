#include <iostream>
#include <vector>
#include <numeric>
#include "for.h"

using namespace std;

//template <class... Ts> struct tuple {};
//
//template <class T, class... Ts>
//struct tuple<T, Ts...> : tuple<Ts...> {
//    tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}
//    T tail;
//};

template <typename T>
int sum(T i) {
    cout << "hello " << i << endl;
    return i;
}

template <typename T, typename... Args>
int sum(T i, Args... ints) {
    cout << "hello " << i << endl;
    return i + sum(ints...);
}

int main () {
//    cout << sum(1, 2, 3) << endl;
    vector<int> one;
    vector<int> two;
    one.resize(3);
    two.resize(3);
    iota(begin(one), end(one), 0);
    iota(begin(two), end(two), one.back());
//    For();
    For<vector<int>, vector<int>> f(one, two);
    function<void(const int, const int)> fun{ [=](const int a, const int b)->void{ cout << a << " " << b << endl; } };
    f.then(fun);
}
