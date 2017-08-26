#include <iostream>
#include <vector>
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
    vector<int> vec;
    vec.resize(5);
//    For();
    For<vector<int>> f(vec);
    f.then([&](int i){ cout << i << endl; });
}
