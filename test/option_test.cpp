#include "option.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

TEST(equality, testNotEqualEmptyNonEmpty2) {
    ASSERT_FALSE(Option<char>() == Option<char>('c'));
}
TEST(equality, testNotEqualEmptyNonEmpty) {
    ASSERT_FALSE(Option<char>('c') == Option<char>());
}
TEST(equality, testEqualEmpty) {
    ASSERT_TRUE(Option<char>() == Option<char>());
}
TEST(equality, testEqualInt) {
    ASSERT_TRUE(Option<int>(6) == Option<int>(6));
}
TEST(equality, testNotEqualInt) {
    ASSERT_FALSE(Option<int>(1) == Option<int>(6));
}

TEST(exists, emptyFalse) {
    auto o = Option<int>();
    ASSERT_FALSE( o.exists([](auto o){ return false; }) );
}
TEST(exists, emptyTrue) {
    auto o = Option<int>();
    ASSERT_FALSE( o.exists([](auto o){ return true; }) );
}
TEST(exists, nonEmptyNotEquals) {
    auto o = Option(15);
    ASSERT_FALSE( o.exists([](auto o){ return o == 16; }) );
}
TEST(exists, nonEmptyEquals) {
    auto o = Option(16);
    ASSERT_TRUE( o.exists([](auto o){ return o == 16; }) );
}

TEST(filter, filterEmpty2) {
    auto o = Option<int>();
    ASSERT_TRUE( o.filter( [](auto o){ return false; } ).isEmpty());
}
TEST(filter, filterEmpty) {
    auto o = Option<int>();
    ASSERT_TRUE( o.filter( [](auto o){ return true; } ).isEmpty());
}
TEST(filter, filterFalse) {
    auto o = Option(16);
    ASSERT_TRUE( o.filter( [](auto o){ return false; } ).isEmpty());
}
TEST(filter, filterTrue) {
    auto o = Option(16);
    ASSERT_TRUE( o.filter( [](auto o){ return true; } ).getOrElse(0) == 16);
}

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

TEST(map, emptyOptionMap) {
    Option<int> number;
    auto result = number.map([](int a) { return 6; });
    ASSERT_TRUE( result.isEmpty() );
}
TEST(map, charStarOptionMap) {
    Option<int> number(1);
    auto result = number.map([](int a) { return "hello there"; });
    ASSERT_TRUE( result == Option("hello there") );
}
TEST(map, stringOptionMap) {
    Option<int> number(1);
    auto result = number.map([](int a) {
        return std::string("hello there ") + std::to_string(a);
    });
    ASSERT_TRUE( result == Option<std::string>("hello there 1") );
}
TEST(map, doubleOptionMap) {
    Option<int> number(1);
    auto result = number.map([](int a) { return 6.0; });
    ASSERT_TRUE( result == Option<double>(6.0) );
}
TEST(map, simpleOptionMap) {
    Option<int> number(1);
    auto result = number.map([](int a) { return 6; });
    ASSERT_TRUE(result == Option<int>(6));
}

TEST(orElse, nonEmpty) {
    Option<int> number(1);
    auto result = number.orElse([]() { return Option<int>(6); });
    ASSERT_TRUE(result == Option<int>(1));
}
TEST(orElse, empty) {
    Option<int> number;
    auto result = number.orElse([]() { return Option<int>(6); });
    ASSERT_TRUE(result == Option<int>(6));
}

TEST(fold, curryNonEmpty) {
    Option<int> number(1);
    auto result = number.fold([]() { return Option<int>(6); });
    auto whatThu = result([](int a) { return Option<int>(a + 1); });
    ASSERT_TRUE(whatThu == Option<int>(2));
}
TEST(fold, curryEmpty) {
    Option<int> number;
    auto result = number.fold([]() { return Option<int>(6); });
    auto whatThu = result([](int a) { return Option<int>(a + 1); });
    ASSERT_TRUE(whatThu == Option<int>(6));
}
TEST(fold, empty) {
    Option<int> number(1);
    auto result = number.fold([]() { return Option<int>(6); })([](int a) { return Option<int>(a + 1); });
    ASSERT_TRUE(result == Option<int>(2));
}
TEST(fold, nonEmpty) {
    Option<int> number;
    auto result = number.fold([]() { return Option<int>(6); })([](int a) { return Option<int>(a + 1); });
    ASSERT_TRUE(result == Option<int>(6));
}
