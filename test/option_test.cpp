#include "option.hpp"
#include <iostream>

using namespace std;

auto assert_true = [](auto f){
    if(f) {
        cout << "assertion passed" << endl;
    } else {
        cout << "assertion failed" << endl;
    }
};
auto assert_eq = [](auto a, auto b){
    if(a == b) {
        cout << "equal" << endl;
    } else {
        cout << "not equal" << endl;
    }
};

int main() {
    auto one = []() {
        Option<int> number;
        number.flatMap([](int a) { return Option<int>(6); });
        return number.isEmpty();
    };
    auto two = [](){
        Option<int> number(5);
        auto result = number.flatMap([](int a) { return Option<int>(a + 1); });
        return result.get();
    };
    assert_true(one());
    assert_eq(two(), 6);
}
