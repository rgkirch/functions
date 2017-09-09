using namespace std;

auto return_some() -> Maybe* {
    return new Some<int>(1);
}

void f(Maybe* m) {
    auto try_some = dynamic_cast<Some<int>*>(m);
    if(try_some != nullptr) {
        cout << "it's a Some\n";
    } else {
        auto try_none = dynamic_cast<None*>(m);
        if(try_none != nullptr) {
            cout << "it's a None\n";
        } else {
            cout << "umm, what?\n";
        }
    }
}

int main() {
    auto thing = return_some();
    Match(some)(
        function<void(Some<int>*)>([](Some<int>*)->void {
            cout << "it's a Some\n";
            })
    )(
        function<void(None*)>([](None*)->void {
            cout << "it's a None\n";
            })

    );
    f(thing);
}
