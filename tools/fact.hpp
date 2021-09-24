
#ifndef _FACT_HPP
#define _FACT_HPP

template <size_t N>
struct precalc_fact {
    size_t arr[N + 1];
    constexpr precalc_fact() : arr() {
        arr[0] = 1;
        for (size_t i = 1; i <= N; ++i) {
            arr[i] = arr[i - 1] * i;
        }
    }
};

#endif //_FACT_HPP

