#include <functional>

using namespace std;

template <typename T>
struct Match {
  Match(T* t) : t(t) {}
    //https://stackoverflow.com/questions/2689709/difference-between-stdresult-of-and-decltype
    // loop into declval and result_of
    template <typename Ret, typename Arg>
    Match& operator()(function<Ret(Arg*)> f) {
      auto cast = dynamic_cast<Arg*>(t);
      if(cast) {
        f(cast);
      }
      // cout << __PRETTY_FUNCTION__ << '\n';
      return *this;
    }
  T* t;
};
