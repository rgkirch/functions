#include <vector>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

struct Object {
    template <typename T>
    Object(T t) : model(new Model<T>(t)) {
        cout << "construct object from T" << endl;
    }
    friend void print(string str) {
        cout << str << endl;
    }
    friend void print(int i) {
        cout << i << endl;
    }
    struct Concept {
        virtual void print() =0;
    };
    template <typename T>
    struct Model : Concept {
        Model() {};
        void print() override {
            cout << "haha" << endl;
        }
    };
    struct Model<string> : Concept {
        Model(string t) : data(t) {}
        void print() override {
            cout << data << endl;
        }
        string data;
    };
    struct Model<int> : Concept {
        Model(int t) : data(t) {}
        void print() override {
            cout << data << endl;
        }
        int data;
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
    void print() {
        for(auto o : objects) {
            o.model->print();
        }
    };
    vector<Object> objects;
};

int main() {
    auto heterogeneous = For(1)(string("hello"));
    function<void(int)> f = [](int i)->void{ cout << i << endl; };
    heterogeneous.print();
}

