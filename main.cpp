#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cassert>

using namespace std;

template<typename T>
struct copy_on_write {
    copy_on_write(T x) : object_m(make_shared<implementation_t>(std::move(x))) {}
    struct implementation_t {
        explicit implementation_t(T x) : value_m(std::move(x)) {}
        T value_m;
    };

    shared_ptr<implementation_t> object_m;
};

template<typename T>
void draw(const T &x, ostream &out, size_t position) { out << string(position, ' ') << x << endl; }

struct object_t {
    template<typename T>
    object_t(const T &x) : object_(new model<T>(x)) {}
    friend void draw(const object_t &x, ostream &out, size_t position) { x.object_->draw_(out, position); }
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

void draw(const vector<copy_on_write<object_t>> &x, ostream &out, size_t position) {
    for (auto &e : x) draw(e.object_m.get()->value_m, out, position + 2);
}

struct my_class_t {
    /* ... */
};

void draw(const my_class_t &, ostream &out, size_t position) { out << string(position, ' ') << "my_class_t" << endl; }

int main() {
    vector<copy_on_write<object_t>> h;
    h.emplace_back(0);
    h.emplace_back(string("Hello!"));
    draw(h, cout, 0);
}
