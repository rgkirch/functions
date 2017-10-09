int main() {
    Cons<0, int> a(0);
    string s = "hello";
    auto b = push_front(s, a);
    return 0;
}
