#include <functional>
#include <type_traits>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <optional>
#include "curry.hpp"

using namespace std;
//using namespace std::experimental;

template <typename T, typename F>
auto optional_bind(optional<T> o, F f) {
    if(o) {
        return f(o.value());
    } else {
        return result_of_t<F(T)>();
    }
}

template <typename F>
auto optionify(F f) {
    return [=](auto x){ return optional(f(x)); };
}

struct Object {
    template <typename T>
    Object(T t) : model(new Model<T>(t)) {}

    template <typename R, typename T>
    auto apply(function<R(T)> f)->optional<R> {
        auto thing = dynamic_cast<Model<T>*>(model);
        if(thing != nullptr) {
            return f(thing->data);
        } else {
            return {};
        }
    }
    struct Concept {
        virtual ~Concept() = default;
    };
    template <typename T>
    struct Model : public Concept {
        Model(T t) : data(t) {}
        T data;
    };

    Concept *model;
};

struct For {
    For(Object o) {
        hetero.push_back(o);
    }
    For& operator()(Object o) {
        hetero.push_back(o);
        return *this;
    }
    template <typename F>
    auto apply(F f) {
        auto fopt = hetero[0].apply(f);
        return optional_bind(fopt, [=](auto f){ return hetero[1].apply(f); });
//        if(fopt) {
//            return hetero[1].apply(fopt.value()).value();
//        } else {
//            return string("error");
//        }
    }
    Comprehension *front, *back;
};

