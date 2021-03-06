
#ifndef _GEN_VECTOR_HPP
#define _GEN_VECTOR_HPP

#include <algorithm>
#include <ctime>
#include <random>
#include <vector>


template<typename T>
std::vector<T> RandomVector(size_t sz) {
    constexpr int RANGE = int(1e9);

    std::mt19937 gen(time(NULL));
    std::uniform_int_distribution<T> uid(-RANGE, RANGE);

    std::vector<T> arr(sz);
    std::generate(arr.begin(), arr.end(),
                  [&uid, &gen]() -> T { return uid(gen); });

    return arr;
}


template<typename T>
std::vector<T> IncreasingVector(size_t sz) {
    std::vector<T> arr(sz);
    std::iota(arr.begin(), arr.end(), 0);
    return arr;
}


template<typename T>
std::vector<T> DecreasingVector(size_t sz) {
    std::vector<T> arr(sz);
    std::iota(arr.rbegin(), arr.rend(), 0);
    return arr;
}

#endif //_GEN_VECTOR_HPP

