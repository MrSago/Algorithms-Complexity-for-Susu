
#ifndef _FLOYD_TEST_HPP
#define _FLOYD_TEST_HPP

#include <iostream>
#include <iomanip>

#include "Floyd.hpp"
#include "matrix.hpp"


template<typename T>
void singleThreadFloydTest(std::vector<int>& matrix_sizes) {
    std::cout << "\n============ Floyd in one thread ============\n\n";
    std::cout << "    " << std::setw(10) << std::left << "Size" << std::setw(15) << std::left << "Time (sec)" << "Operations\n";
    for (auto& sz : matrix_sizes) {
        ops = 0;
        T** matrix = newMatrix<T>(sz);
        randomMatrix(matrix, sz);
        long long time_calc = Floyd(matrix, sz);
        std::cout << "    " << std::setw(10) << std::left << sz << std::setw(15) << std::left << time_calc * 1e-9 << ops << '\n';
        freeMatrix(matrix, sz);
    }
    std::cout << "=============================================\n\n";
}


template<typename T>
void multiThreadFloydTest(std::vector<int>& matrix_sizes, int threads) {
    std::cout << "\n============ Floyd in " << threads << " thread ============\n\n";
    std::cout << "    " << std::setw(10) << std::left << "Size" << std::setw(15) << std::left << "Time (sec)" << "Operations\n";
    for (auto& sz : matrix_sizes) {
        ops = 0;
        T** matrix = newMatrix<T>(sz);
        randomMatrix(matrix, sz);
        long long time_calc = FloydParallel(matrix, sz, threads);
        std::cout << "    " << std::setw(10) << std::left << sz << std::setw(15) << std::left << time_calc * 1e-9 << ops << '\n';
        freeMatrix(matrix, sz);
    }
    std::cout << "============================================\n\n";
}

#endif //_FLOYD_TEST_HPP

