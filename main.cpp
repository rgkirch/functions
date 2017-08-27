#include <vector>
#include <functional>
#include <iostream>

using namespace std;

struct Object {
    template <typename T>
    Object(T t) : model(new Model<T>(t)) {
        cout << "construct object from T" << endl;
    }
    struct Concept {
        virtual void print() =0;
//        template <typename T>
//        virtual void apply(function<void(T)> f) =0;
    };
    template <typename T>
    struct Model : Concept {
        Model(T t) : data(t) {}
        void print() {
            cout << data << endl;
        }
//        void apply(function<void(T)> f) {
//            f(data);
//        }
        T data;
    };
    Concept *model;
};

struct For {
    For() {
        cout << "default construct For" << endl;
    }
    For(Object o) {
        cout << "construct For from object and push back" << endl;
        objects.push_back(o);
    }
    For operator()(Object o) {
        cout << "push back object" << endl;
        objects.push_back(o);
        return *this;
    }
    template <typename T>
    void apply(function<void(T)> f) {
        for(auto o : objects) {
//            o.model->apply(f);
        }
    };
    vector<Object> objects;
};

int main() {
    auto heterogenious = For(1)("hello");
    function<void(int)> f = [](int i)->void{ cout << i << endl; };
    heterogenious.apply(f);
}

