#include <iostream>
#include <memory>
#include <string>
#include "maybe.hpp"

using namespace std;

template <typename T>
struct id {
    using type = T;
};

//template <typename T>
//using type_of = typename T::type;
//
//template <int n, typename... Args>
//struct Get;
//
//template <int n, typename T, typename... Args>
//struct Get<n, T, Args...> : Get<n-1, Args...> {};
//
//template <typename T, typename... Args>
//struct Get<0, T, Args...> : id<T> {};
//
//template <int n, typename... Args>
//using get = type_of <Get <n, Args...> >;

template <int n, typename T, typename... Args>
struct Cons {
    Cons(T t, Cons<n-1, Args...> c) : head(t), tail(c) {}
    T head;
    Cons<n-1, Args...> tail;
    using type = T;
};

template <typename T>
struct Cons<0, T> {
    Cons(T t) : head(t) {}
    T head;
};

template <typename T>
auto pop_front(Cons<0, T> c) {
    return make_pair(c.head, None());
}

template <int n, typename T, typename... Args>
auto pop_front(Cons<n, T, Args...> c) -> pair<T, Cons<n-1, Args...>> {
    return make_pair(c.head, c.tail);
}

template <int n, typename T, typename... Args>
auto push_front(T t, Cons<n, Args...> c) -> Cons<n+1, T, Args...> {
    return Cons<n+1, T, Args...>(t,c);
}

template <typename T, typename Arg>
auto push_back(T t, Cons<0, Arg> c) -> Cons<1, Arg, T> {
    auto b = Cons<0, T>(t);
    return push_front(c.head, b);
}

template <int n, typename T, typename... Args>
auto push_back(T t, Cons<n, Args...> c) -> Cons<n+1, Args..., T> {
    auto [head, tail] = pop_front(c);
    auto new_tail = push_back(t, tail);
    return push_front(head, new_tail);
}

int main() {
    Cons<0, int> a(0);
    string s = "hello";
    auto b = push_front(s, a);
    return 0;
}
