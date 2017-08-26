#pragma once

#include <iostream>
#include <functional>

using namespace std;

template <typename... Es>
struct For {
    For() {
        cout << "For base constructor\n" << __PRETTY_FUNCTION__ << endl;
    }
//    template <typename T>
    void then(function<void()> f) {
        f();
    }
};

template <typename E, typename... Es>
struct For<E, Es...> : For<Es...> {
    typedef For<Es...> super;
    For(E e, Es... es) : super(es...) {
        cout << "For child constructor\n" << __PRETTY_FUNCTION__ << endl;
        value = e;
    }
    template <typename... Args>
    void then(function<void(Args...)> f) {
        for(auto e : value) {
            function<void(const int)> fp = [=](const int i){ f(e, i); };
//            auto fp = bind(f, e, std::placeholders::_2);
            super::then(fp);
//            ((For<Es...>*)this)->then(fp);
//            f(e);
        }
    }
    E value;
};


