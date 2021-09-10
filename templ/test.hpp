
#ifndef _TEST_HPP
#define _TEST_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#include "gen.hpp"
#include "sort.hpp"


template<typename T>
void _print_vector(std::vector<T>& arr) {
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
}


template<typename T>
void _run_test(std::vector<T> (*gen_fun)(size_t), long long (*sort_fun)(T*, int), std::vector<size_t>& arr_sizes) {
    extern size_t ops;
    std::cout << "    " << std::setw(10) << std::left << "Size" << std::setw(15) << std::left << "Time (sec)" << "Operations\n";
    for (auto& sz : arr_sizes) {
        ops = 0;
        std::vector<T> arr = gen_fun(sz);
        long long time_calc = sort_fun(arr.data(), static_cast<int>(arr.size()));
        if (!_check_sort(arr.data(), static_cast<int>(arr.size()))) {
            throw std::runtime_error("Array not sorted!");
        }
        std::cout << "    " << std::setw(10) << std::left << sz << std::setw(15) << std::left << time_calc * 1e-9 << ops << '\n';
    }
    std::cout << '\n';
}


template<typename T>
void startTestSort(const char sort_name[], long long (*sort_fun)(T*, int), std::vector<size_t>& arr_sizes) {
    std::cout << "\n============ " << sort_name << " ============\n\n";

    std::cout << "Increasing array:\n";
    _run_test(increasingVector, sort_fun, arr_sizes);

    std::cout << "Random array:\n";
    _run_test(randomVector, sort_fun, arr_sizes);

    std::cout << "Decreasing array:\n";
    _run_test(decreasingVector, sort_fun, arr_sizes);

    std::cout << "=============" << std::string(strlen(sort_name), '=') << "=============\n\n";
}

#endif //_TEST_HPP

