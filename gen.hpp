
#ifndef _GEN_HPP
#define _GEN_HPP

#include <vector>
#include <random>

constexpr int RANGE = int(1e9);


template<typename T>
std::vector<T> randomVector(size_t sz) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<T> uid(-RANGE, RANGE);
    std::vector<T> arr(sz);
    for (auto& it : arr) {
        it = uid(gen);
    }
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
    for (auto& it: arr) {
        it = static_cast<T>(sz--);
    }
    return arr;
}

#endif //_GEN_HPP

