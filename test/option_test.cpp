#include "option.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

TEST(flatMap, returnSix) {
    Option<int> number(1);
    auto result = number.flatMap([](int a) { return Option(6); });
    ASSERT_TRUE(result == Option<int>(6));
}

TEST(flatMap, emptyStaysEmpty) {
    Option<int> number;
    auto result = number.flatMap([](int a) { return Option(6); });
    ASSERT_TRUE(result.isEmpty());
}

TEST(flatMap, happyPathFlatMap) {
    Option<int> number(5);
    auto result = number.flatMap([](int a) { return Option(a + 1); });
    ASSERT_EQ(result.getOrElse(0), 6);
}

TEST(flatMap, gonnaBreakIt) {
    Option<int> number(5);
    auto result = number.flatMap([](double a) { return Option<int>(a + 1); });
    ASSERT_EQ(result.getOrElse(0), 6);
}
