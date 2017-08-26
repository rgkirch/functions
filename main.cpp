#include <iostream>
#include "for.h"

using namespace std;

//template <class... Ts> struct tuple {};
//
//template <class T, class... Ts>
//struct tuple<T, Ts...> : tuple<Ts...> {
//    tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}
//    T tail;
//};

template <typename... Args>
struct Sum {
    Sum() : value(0) {}
    int value;
};

template <class T, class... Args>
struct Sum<T, Args...> : Sum<Args...> {
    Sum(T t, Args... ints) : Sum<Args...>(ints...) {
        cout << "hello " << t << endl;
        value = t + ((Sum<Args...>*)this)->value;
    }
    T value;
};

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

template <int n, typename T>
struct Cons {
    Cons<n - 1, T> c;
    T t;
};

template <typename T>
struct Cons<0, T> {
    T t;
};

//template <typename T, typename... Ts>
//struct For {
//    For<n - 1, T> c;
//    T t;
//};
//
//template <typename T>
//struct For<0, T> {
//    T t;
//};

int main () {
    cout << sum(1, 2, 3) << endl;
    cout << Sum<int, int, int>(1, 2, 3).value << endl;
    Cons<6, int> c;
    c.t = 6;
    c.c.t = 5;
    c.c.c.t = 2;
}
