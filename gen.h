
#ifndef _GEN_H
#define _GEN_H

#include <vector>
#include <random>
#include <ctime>

constexpr int RANGE = int(1e6);


template<typename T>
std::vector<T> randomVector(size_t sz) {
    std::mt19937 gen(time(NULL)); 
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
        it = --sz;
    }
    return arr;
}

#endif //_GEN_H

