#pragma once

#include "option.hpp"

template <typename T>
class Option;

template <typename T>
struct is_option {
    static const bool value = false;
};

template <typename N>
struct is_option<Option<N>> {
    static const bool value = true;
};
