
#ifndef _GEN_VECTOR_HPP
#define _GEN_VECTOR_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

constexpr int RANGE = int(1e9);


template<typename T>
std::vector<T> randomVector(size_t sz) {
    std::mt19937 gen(time(NULL));
    std::uniform_int_distribution<T> uid(-RANGE, RANGE);
    std::vector<T> arr(sz);
    std::generate(arr.begin(), arr.end(),
                  [&uid, &gen]() -> T { return uid(gen); });
    return arr;
}


template<typename T>
std::vector<T> increasingVector(size_t sz) {
    std::vector<T> arr(sz);
    std::iota(arr.begin(), arr.end(), 0);
    return arr;
}


template<typename T>
std::vector<T> decreasingVector(size_t sz) {
    std::vector<T> arr(sz);
    std::iota(arr.rbegin(), arr.rend(), 0);
    return arr;
}

#endif //_GEN_VECTOR_HPP

