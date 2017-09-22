template <typename T>
struct Maybe {
  // make_none() {
  //   return 
  // }
    virtual ~Maybe() =0;
};

template <typename T>
Maybe<T>::~Maybe() {}

template <typename T>
struct Some : public Maybe<T> {
    Some() =delete;
    Some(T t) : value(t) {}
    ~Some() {}
    T value;
};

template <typename T>
struct None : public Maybe<T> {
    ~None() {}
};
