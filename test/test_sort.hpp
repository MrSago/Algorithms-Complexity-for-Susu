
#ifndef _TEST_SORT_HPP
#define _TEST_SORT_HPP

#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../algo/sort.hpp"
#include "../tools/gen_vector.hpp"


template<typename T>
void __run_test_sort(std::vector<T> (*gen_fun)(size_t),
                    long long (*sort_fun)(T*, size_t),
                    const std::vector<size_t>& arr_sizes) {
    extern size_t ops;

    std::cout << "    "
              << std::setw(15) << std::left << "Size"
              << std::setw(15) << std::left << "Time (sec)"
              << "Operations\n";

    for (auto& sz : arr_sizes) {
        ops = 0;

        std::vector<T> arr = gen_fun(sz);
        long long time_calc = sort_fun(arr.data(), sz);

        if (!CheckSort(arr.data(), sz)) {
            throw std::runtime_error("Array not sorted!");
        }

        std::cout << "    "
                  << std::setw(15) << std::left << sz
                  << std::setw(15) << std::left << time_calc * 1e-9
                  << ops << '\n';
    }

    std::cout << '\n';
}


template<typename T>
void StartTestSort(const char sort_name[],
                   long long (*sort_fun)(T*, size_t),
                   const std::vector<size_t>& arr_sizes) {
    std::cerr << '\n' << sort_name << " test...";

    std::cout << "\n============== " << sort_name << " ==============\n\n";

    std::cout << "Increasing array:\n";
    __run_test_sort(IncreasingVector, sort_fun, arr_sizes);

    std::cout << "Random array:\n";
    __run_test_sort(RandomVector, sort_fun, arr_sizes);

    std::cout << "Decreasing array:\n";
    __run_test_sort(DecreasingVector, sort_fun, arr_sizes);

    std::cout << "===============" << std::string(strlen(sort_name), '=') << "===============\n\n";
}

#endif //_TEST_SORT_HPP

