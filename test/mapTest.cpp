#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

struct Object {
    Object(int d) : data(d) {
        cout << "object construction with " << data << endl;
    }
    int data;
};

int main() {
    unordered_map<int, unique_ptr<Object>> m;
    m[0] = make_unique<Object>(0);
    m[0] = make_unique<Object>(1);
    m.insert(make_pair(1, make_unique<Object>(0)));
    m.insert(make_pair(1, make_unique<Object>(1)));
    cout << m[0].get()->data << endl;
    cout << m[1].get()->data << endl;
}

//    Object(Object& o) : data(o.data) {
//        cout << "object copy from " << data << endl;
//    }
//    Object(Object&& o) : data(move(o.data)) {
//        cout << "object move from " << data << endl;
//    }
//~Object() {}
