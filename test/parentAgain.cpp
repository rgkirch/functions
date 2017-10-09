namespace detail {
    template <typename TL> void Verify     (int, int[]) {}
    template <>            void Verify<int>(int, int[]) {}
}

template<typename T> class Constraint {
    // ...
    template <typename TL> void Verify(int position, int constraints[]) {
        detail::Verify<TL>(position, constraints);
    }
};
