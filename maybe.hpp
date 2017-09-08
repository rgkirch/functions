struct Maybe {
    virtual ~Maybe() =0;
};

Maybe::~Maybe() {}

template <typename T>
struct Some : Maybe {
    Some() =delete;
    Some(T t) : value(t) {}
    ~Some() override {}
    T value;
};

struct None : Maybe {
    ~None() override {}
};
