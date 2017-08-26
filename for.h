#pragma once

#include <iostream>

using namespace std;

template <typename... Es>
struct For {
    For() : value(0) {}
    int value;
};

template <typename E, typename... Es>
struct For<E, Es...> : For<Es...> {
    For(E e, Es... es) : For<Es...>(es...) {
//        value = e + ((For<Es...>*)this)->value;
        value = e;
    }
    template <typename F>
    void then(F f) {
        for(auto e : value) {
            f(e);
        }
    }
    E value;
};


