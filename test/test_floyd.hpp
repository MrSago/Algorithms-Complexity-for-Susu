
#ifndef _FLOYD_TEST_HPP
#define _FLOYD_TEST_HPP

#include <iostream>
#include <iomanip>
#include <ctime>

#include "../algo/floyd.hpp"
#include "../tools/matrix.hpp"


template<typename T>
void singleThreadFloydTest(std::vector<size_t>& matrix_sizes) {
    std::cout << "\n============ Floyd in one thread ============\n";

    std::cout << "    "
              << std::setw(15) << std::left << "Size"
              << std::setw(15) << std::left << "Time (sec)"
              << "Operations\n";

    for (auto& sz : matrix_sizes) {
        int sz_int = static_cast<int>(sz);
        ops = 0;

        T** matrix = newMatrix<T>(sz_int);
        randomMatrix(matrix, sz_int, time(0));
        long long time_calc = Floyd(matrix, sz_int);

        std::cout << "    "
                  << std::setw(15) << std::left << sz_int
                  << std::setw(15) << std::left << time_calc * 1e-9
                  << ops << '\n';

        freeMatrix(matrix, sz_int);
    }

    std::cout << "=============================================\n\n";
}


template<typename T>
void multiThreadFloydTest(std::vector<size_t>& matrix_sizes, int threads) {
    std::cout << "\n============ Floyd in " << threads << " threads ============\n";

    std::cout << "    "
              << std::setw(15) << std::left << "Size"
              << std::setw(15) << std::left << "Time (sec)"
              << "Operations\n";

    for (auto& sz : matrix_sizes) {
        int sz_int = static_cast<int>(sz);
        ops = 0;

        T** matrix = newMatrix<T>(sz_int);
        randomMatrix(matrix, sz_int, time(0));
        long long time_calc = FloydParallel(matrix, sz_int, threads);

        std::cout << "    "
                  << std::setw(15) << std::left << sz_int
                  << std::setw(15) << std::left << time_calc * 1e-9
                  << ops << '\n';

        freeMatrix(matrix, sz_int);
    }

    std::cout << "=============================================\n\n";
}

#endif //_FLOYD_TEST_HPP

