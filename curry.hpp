#include <functional>
using namespace std;
template <typename R, typename T, typename... Args>
auto curry(const function<R(T, Args...)> f) {
    return [=](T t) {
        return [=](Args... args){ return f(t, args...); };
    };
}