
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


template<typename T>
void _print_vector(std::vector<T>& arr) {
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
}


template<typename T>
void _run_test(std::vector<T> (*gen_fun)(size_t), long long (*sort_fun)(std::vector<T>&)) {
    std::vector<std::pair<int, long long>> result;

    for (auto& sz : ARR_SIZE) {
        std::vector<T> arr = gen_fun(sz);
        long long time = sort_fun(arr);
        if (!checkSort(arr)) {
            throw std::runtime_error("Array not sorted!");
        }
        result.push_back( { sz, time } );
    }

    std::cout << "    " << std::setw(10) << std::left << "Size" << "Time (sec)\n";
    for (auto& it : result) {
        std::cout << "    " << std::setw(10) << std::left << it.first << it.second * 1e-9 << '\n';
    }
    std::cout << '\n';
}


template<typename T>
void startTestSort(const char sort_name[], long long (*sort_fun)(std::vector<T>&)) {
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

