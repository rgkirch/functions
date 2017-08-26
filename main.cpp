#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cassert>

using namespace std;

template<typename T>
void draw(const T &x, ostream &out, size_t position) { out << string(position, ' ') << x << endl; }

struct Object {
    template<typename T>
    Object(const T &x) : object_(new model<T>(x)) {}
    friend void draw(const Object &o, ostream &out, size_t position) { o.object_->then(out, position); }
    struct concept_t {
        virtual ~concept_t() = default;
        virtual concept_t *copy_() = 0;
        virtual void then(ostream &, size_t) const = 0;
    };

    template<typename T>
    struct model : concept_t {
        model(const T &x) : data_(x) {}
        concept_t *copy_() { return new model(*this); }
        void then(ostream &out, size_t position) const { draw(data_, out, position); }
        T data_;
    };

    unique_ptr<concept_t> object_;
};

struct Indirection {
    Indirection(Object x) : object_m(make_shared<implementation_t>(std::move(x))) {}
    struct implementation_t {
        explicit implementation_t(Object x) : value_m(std::move(x)) {}
        Object value_m;
    };
    shared_ptr<implementation_t> object_m;
};

void draw(const vector<Indirection> &x, ostream &out, size_t position) {
    for (auto &e : x) draw(e.object_m.get()->value_m, out, position + 2);
}

struct my_class_t {
    /* ... */
};

void draw(const my_class_t &, ostream &out, size_t position) { out << string(position, ' ') << "my_class_t" << endl; }

int main() {
    vector<Indirection> h;
    h.emplace_back(0);
    h.emplace_back(string("Hello!"));
    draw(h, cout, 0);
}
