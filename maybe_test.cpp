#include <iostream>
#include "maybe.hpp"

using namespace std;

void f(Maybe<int>* m) {
  auto s = dynamic_cast<Some<int>*>(m);
  if(s) {
    cout << "it's a some" << endl;
  } else {
    cout << "it's not a some" << endl;
  }
}

int main() {
  Some number(4);
  f(&number);
  return 0;
}
