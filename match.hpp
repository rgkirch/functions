struct Match {
    template <typename T>
    Match(T t) {}
    template <typename Ret, typename Arg>
    Match& operator()(function<Ret(Arg)> f) {
        cout << "hi from case \n";
        cout << __PRETTY_FUNCTION__ << '\n';
        return *this;
    }
};
