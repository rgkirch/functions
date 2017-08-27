#include <vector>
#include <iostream>

using namespace std;

struct Object {
    template <typename T>
    Object(T t) : model(new Model<T>(t)) {}
    struct Concept {
        virtual void print() =0;
    };
    template <typename T>
    struct Model : Concept {
        Model(T t) : data(t) {}
        void print() {
            cout << data << endl;
        }
        T data;
    };
    Concept *model;
};

int main() {
    vector<Object> vect;
    vect.push_back(0);
    vect.push_back("hello");
    vect[0].model->print();
    vect[1].model->print();
}

