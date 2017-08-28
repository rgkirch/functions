#include <vector>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

//template <typename T>
//void print(T&&);      // <- so that Object::Model knows what you want.

void print(const std::string &s) {
    std::cout << s << '\n';
}

void print(const int i) {
    std::cout << i << '\n';
}

struct Object {

    template<typename T>
    Object(T t) : model(new Model<T>(t)) {
        cout << "construct object from T" << endl;
    }

    struct Concept {
        virtual ~Concept() = default;

        virtual void apply() =0;
    };

    template<typename T>
    struct Model : Concept {
        Model(T t) : data(t) {}

        void apply() {
            print(data);
        }

        T data;
    };

    Concept *model;

};


//template<>
//struct Object::Model<int> : Concept {
//    Model(int t) : data(t) {}
//
//    void print() {
//        ::print(data);
//    }
//
//    int data;
//};
//
//template<>
//struct Object::Model<string> : Concept {
//    Model(string t) : data(t) {}
//
//    void print() {
//        ::print(data);
//    }
//
//    string data;
//};

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
        for (auto o : objects) {
            o.model->apply();
        }
    };

    vector<Object> objects;
};

int main() {
    auto heterogeneous = For(1)(string("hello"));
    heterogeneous.print();
}

//    function<function<void(std::string)>(int)> f = [&](int i) -> function<void(std::string)> {
//        function<void(std::string)> g = [&](string str) -> void {
//            cout << i << ' ' << str << endl;
//        };
//        return g;
//    };
//    heterogeneous.yield(f);

//    void yield(function<function<void(std::string)>(int)> f) {
//        for (auto ints : objects[0]) {
//            function<void(std::string)> g = o.apply(f);
//        }
//    }
