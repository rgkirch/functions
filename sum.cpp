#include <iostream>
#include "for.h"

using namespace std;

template <typename... Args>
struct Sum {
    Sum() : value(0) {}
    int value;
};

template <class T, class... Args>
struct Sum<T, Args...> : Sum<Args...> {
    Sum(T t, Args... ints) : Sum<Args...>(ints...) {
        value = t + ((Sum<Args...>*)this)->value;
    }
    T value;
};

int main () {
    cout << Sum<int, int, int, int>(1, 2, 3, 4).value << endl;
}
