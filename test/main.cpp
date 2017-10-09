int main() {
    auto a = For(std::string("hello"),42)(1,-1);
    auto b = a;
    b('a','b','c');
    std::cout <<"a:\n";
    print(a);
    std::cout <<"b:\n";
    print(b);
}
