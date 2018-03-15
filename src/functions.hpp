#pragma once
#include <functional>
using namespace std;

template <typename B, typename C> struct Function {
  Function(function<C(B)> g) : g(g) {}
  template <typename A> Function<A, C> andThen(function<B(A)> f) {
    return function<C(A)>([=](A a) { return f(g(a)); });
  }
  template <typename D> Function<B, D> compose(function<D(C)> h) {
    return function<D(B)>([=](B b) { return g(h(b)); });
  }
  C operator()(B b) { return g(b); }
  function<C(B)> g;
};