#include <iostream>
#include <functional>
#include "maybe.hpp"
#include "match.hpp"

using namespace std;

auto return_some() -> Maybe<int>* {
  return static_cast<Maybe<int>*>(new Some(1));
}

void f(Maybe<int>* m) {
    auto try_some = dynamic_cast<Some<int>*>(m);
    if(try_some != nullptr) {
        cout << "it's a Some\n";
    } else {
      auto try_none = dynamic_cast<None<int>*>(m);
        if(try_none != nullptr) {
            cout << "it's a None\n";
        } else {
            cout << "umm, what?\n";
        }
    }
}

int main() {
    auto thing = return_some();
    Match match(thing);
    match(
      std::function<void(Some<int>*)>([](Some<int>*)->void {
          cout << "it's a Some\n";
          })
    )(
      std::function<void(None<int>*)>([](None<int>*)->void {
          cout << "it's a None\n";
          })

    );
    // f(thing);
}
