#include "option.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

TEST(flatMap, emptyStaysEmpty) {
    Option<int> number;
    number.flatMap([](int a) { return Option<int>(6); });
    ASSERT_TRUE(number.isEmpty());
}

TEST(flatMap, happyPathFlatMap) {
    Option<int> number(5);
    auto result = number.flatMap([](int a) { return Option<int>(a + 1); });
    ASSERT_EQ(result.get(), 6);
}
