#include <iostream>
#include <functional>
#include "curry.hpp"
using namespace std;

int main() {
    auto sum = [=](auto a, auto b, auto c){ return a + b + c; };
    auto curried = curry(sum);
    cout << curried(1)(2)(3) << endl;

}