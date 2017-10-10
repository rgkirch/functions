#pragma once

#include <type_traits>
#include <functional>
#include "option_traits.hpp"

template <typename T>
struct is_option;

template <typename A>
class Option {
private:
    A data;
    const bool empty;
public:
    Option() : empty(true) {}

    Option(A d) : data(d), empty(false) {} // check not null

//    final def exists(p: (A) ⇒ Boolean): Boolean
//    Returns true if this option is nonempty and the predicate p returns true when applied to this scala.Option's value. Otherwise, returns false.

//    final def filter(p: (A) ⇒ Boolean): Option[A]
//    Returns this scala.Option if it is nonempty and applying the predicate p to this scala.Option's value returns true. Otherwise, return None.

//    final def flatMap[B](f: (A) ⇒ Option[B]): Option[B]
//    Returns the result of applying f to this scala.Option's value if this scala.Option is nonempty. Returns None if this scala.Option is empty. Slightly different from map in that f is expected to return an scala.Option (which could be None).
    template<typename F>
//    auto flatMap(F f) const -> typename std::enable_if<is_option<decltype(f(data))>::value, decltype(f(data))>::type {
    auto flatMap(F f) const -> std::enable_if_t <is_option<std::result_of_t<F(A)>>::value, std::result_of_t<F(A)>> {
        if (this->isEmpty()) {
            return {};
        } else {
            return f(data);
        }
    }

//    final def fold[B](ifEmpty: ⇒ B)(f: (A) ⇒ B): B
//    Returns the result of applying f to this scala.Option's value if the scala.Option is nonempty. Otherwise, evaluates expression ifEmpty.

//    final def getOrElse[B >: A](default: ⇒ B): B
//    Returns the option's value if the option is nonempty, otherwise return the result of evaluating default.
    template <typename F>
    auto getOrElse(F f) -> std::enable_if_t< std::is_same<A, std::result_of_t <F>>::type, A > {
        if (this->isEmpty()) {
            return f();
        } else {
            return data;
        }
    }
    auto getOrElse(auto f) {
        if (this->isEmpty()) {
            return f;
        } else {
            return data;
        }
    }

//    final def map[B](f: (A) ⇒ B): Option[B]
//    Returns a scala.Some containing the result of applying f to this scala.Option's value if this scala.Option is nonempty. Otherwise return None.
    template<typename F>
    auto map(F f) -> Option<decltype(f(data))> {
        if (this->isEmpty()) {
            return {};
        } else {
            return Option(f(data));
        }
    }

//    final def nonEmpty: Boolean
//    Returns false if the option is None, true otherwise.

//    final def orElse[B >: A](alternative: ⇒ Option[B]): Option[B]
//    Returns this scala.Option if it is nonempty, otherwise return the result of evaluating alternative.


//    Option<A> &map(std::function<Option<A>(A)> &f) {
//        if (not this->isEmpty()) {
//            Option<A> o = f(this->data);
//            if (not o.isEmpty()) {
//                this->data = o.data;
//            } else {
//                this->empty = true;
//            }
//        }
//        return *this;
//    }

    bool isEmpty() const {
        return this->empty;
    }

    template<typename F>
    auto getOrElse(F f) -> typename std::enable_if<std::is_same<A, decltype(f())>::value>::type {

        if (not this->isEmpty())
            return data;
        else
            return f();
    }

    A getOrElse(A e) {
        if (not this->isEmpty())
            return data;
        else
            return e;
    }

    auto get() {
        return data;
    }

};
