#pragma once

#include <iostream>
#include <memory>
#include <functional>

using namespace std;

template <typename T>
struct For {
//    typedef For<Args...> super;
    For(T t) : t(t) {
        cout << __PRETTY_FUNCTION__ << endl;
    }
    template <typename E>
    auto operator()(E e) {
        f = make_unique<For>(e);
    }
    template <typename F>
    void then(F f) {
        for(auto e : t) {
            auto fp = f(e);
            f->then(fp);
        }
    }
    T t;
    unique_ptr<For> f;
};


