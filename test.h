
#ifndef _TEST_H
#define _TEST_H

#include <vector>

constexpr int ARR_SIZE[] = {
    1000, 2000, 3500, 6000, 10000, 15000, 20000, 30000, 50000
};

using test_t = std::vector<std::pair<int, long long>>;


template<typename T>
void printVector(std::vector<T>& arr) {
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
}


template<typename T>
test_t testSort(std::vector<T> (*gen_fun)(size_t), long long (*sort_fun)(std::vector<T>&)) {
    test_t result;
    for (auto& sz : ARR_SIZE) {
        std::vector<T> arr = gen_fun(sz);
        long long time = sort_fun(arr);
        if (!checkSort(arr)) {
            throw std::runtime_error("Array not sorted!");
        }
        result.push_back( { sz, time } );
    }
    return result;
}

#endif //_TEST_H

