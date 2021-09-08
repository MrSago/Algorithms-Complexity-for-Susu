
#ifndef _TEST_HPP
#define _TEST_HPP

#include <iostream>
#include <iomanip>
#include <vector>

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
void _run_test(std::vector<T> (*gen_fun)(size_t), long long (*sort_fun)(T*, int, size_t&), std::vector<size_t>& arr_sizes) {
    std::cout << "    " << std::setw(10) << std::left << "Size" << std::setw(15) << std::left << "Time (sec)" << "Operations\n";
    for (auto& sz : arr_sizes) {
        size_t ops = 0;
        std::vector<T> arr = gen_fun(sz);
        long long time_calc = sort_fun(arr.data(), (int)arr.size(), ops);
        if (!_check_sort(arr.data(), (int)arr.size())) {
            throw std::runtime_error("Array not sorted!");
        }
        std::cout << "    " << std::setw(10) << std::left << sz << std::setw(15) << std::left << time_calc * 1e-9 << ops << '\n';
    }
    std::cout << '\n';
}


template<typename T>
void startTestSort(const char sort_name[], long long (*sort_fun)(T*, int, size_t&), std::vector<size_t>& arr_sizes) {
    std::cout << "\n============ " << sort_name << " ============\n\n";

    std::cout << "Best case (increasing array):\n";
    _run_test(increasingVector, sort_fun, arr_sizes);

    std::cout << "Avarage case (random array):\n";
    _run_test(randomVector, sort_fun, arr_sizes);

    std::cout << "Worst case (decreasing array):\n";
    _run_test(decreasingVector, sort_fun, arr_sizes);

    std::cout << "========================================\n\n";
}

#endif //_TEST_HPP

