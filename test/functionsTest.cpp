#include "functions.hpp"
#include <functional>
#include <gtest/gtest.h>

using namespace std;
TEST(sanity, one) { cout << "hello world" << endl; }

TEST(compose, one) {
  auto triple = function<int(int)>([=](int a) { return a * 3; });
  auto pred = [=](int a) { return a - 1; };
  auto predComposeTripple = Function<int, int>(pred).compose(triple);
  ASSERT_EQ(29, predComposeTripple(10));
}

TEST(andThen, one) {
  auto triple = function<int(int)>([=](int a) { return a * 3; });
  auto pred = [=](int a) { return a - 1; };
  auto predAndThenTriple = Function<int, int>(pred).andThen(triple);
  ASSERT_EQ(27, predAndThenTriple(10));
}

TEST(sanity, two) { pair p(1, "hello"); }