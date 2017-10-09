int main() {
    auto f = (function<string(int, string)>)[=](int i, string str){
        stringstream ss;
        cout << "i is " << i << endl;
        ss << i << ' ' << str << endl;
        return ss.str();
    };
    auto result = For(1)(string("hello")).apply((function<function<string(string)>(int)>)curry(f));
    cout << "result! " << result.value() << endl;

//    function<void(int)> f = [&](int i){
//        std::cout << i << std::endl;
//    };
//    comprehension.apply(f);
}
