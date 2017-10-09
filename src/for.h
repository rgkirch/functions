#pragma once

#include <iostream>
#include <memory>
#include <functional>

using namespace std;

class object_t {
public:
    template<typename T>
    object_t(const T &x) : object_(new model<T>(x)) {}
    object_t(const object_t &x) : object_(x.object_->copy_()) { cout << "copy" << endl; }
    object_t(object_t &&x) = default;
    object_t &operator=(object_t x) {
        object_ = move(x.object_);
        return *this;
    }

    friend void draw(const object_t &x, ostream &out, size_t position) { x.object_->draw_(out, position); }

private:
    struct concept_t {
        virtual ~concept_t() = default;
        virtual concept_t *copy_() = 0;
        virtual void draw_(ostream &, size_t) const = 0;
    };

    template<typename T>
    struct model : concept_t {
        model(const T &x) : data_(x) {}
        concept_t *copy_() { return new model(*this); }
        void draw_(ostream &out, size_t position) const { draw(data_, out, position); }
        T data_;
    };

    unique_ptr <concept_t> object_;
};

template <typename T>
struct For {
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
    shared_ptr<object_t> object_m;
};


