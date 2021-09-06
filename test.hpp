
#ifndef _TEST_HPP
#define _TEST_HPP

#include <iostream>
#include <iomanip>
#include <vector>

#include "gen.hpp"
#include "sort.hpp"

constexpr int ARR_SIZE[] = {
    1000, 2000, 3500, 6000, 10000, 15000, 20000, 30000, 50000, 100000
};

using test_t = std::vector<std::pair<int, long long>>;


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


template<typename T>
void _print_vector(std::vector<T>& arr) {
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
}


void _test_print(test_t t) {
    for (auto& it : t) {
        std::cout << "    " << std::setw(10) << std::left << it.first << it.second * 1e-9 << '\n';
    }
    std::cout << '\n';
}


template<typename T>
void _run_test(std::vector<T> (*gen_fun)(size_t), long long (*sort_fun)(std::vector<T>&)) {
    std::cout << "    " << std::setw(10) << std::left << "Size" << "Time (sec)\n";
    test_t test_res = testSort(gen_fun, sort_fun);
    _test_print(test_res);
}


template<typename T>
void startTestSort(std::string sort_name, long long (*sort_fun)(std::vector<T>&)) {
    std::cout << "\n============ " << sort_name << " ============\n\n";

    std::cout << "Best case (increasing array):\n";
    _run_test(increasingVector, sort_fun);

    std::cout << "Avarage case (random array):\n";
    _run_test(randomVector, sort_fun);

    std::cout << "Worst case (decreasing array):\n";
    _run_test(decreasingVector, sort_fun);

    std::cout << "========================================\n\n";
}

#endif //_TEST_HPP

