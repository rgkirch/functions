#include <functional>
using namespace std;

template <typename R, typename T>
auto curry(const function<R(T)> f) {
    cout << __PRETTY_FUNCTION__ << endl;
    return f;
}
template <typename R, typename T, typename... Args>
auto curry(const function<R(T, Args...)> f) {
    cout << __PRETTY_FUNCTION__ << endl;
    return [=](T t) {
        return curry((function<R(Args...)>)[=](Args... args){ return f(t, args...); });
    };
}