
#ifndef _TEST_FLOYD_HPP
#define _TEST_FLOYD_HPP

#include <iostream>
#include <iomanip>
#include <ctime>

#include "../algo/floyd.hpp"
#include "../tools/matrix.hpp"


template<typename T>
void singleThreadFloydTest(std::vector<size_t>& matrix_sizes) {
    extern size_t ops;

    std::cout << "\n============ Floyd in one thread ============\n";

    std::cout << "    "
              << std::setw(15) << std::left << "Size"
              << std::setw(15) << std::left << "Time (sec)"
              << "Operations\n";

    for (auto& sz : matrix_sizes) {
        ops = 0;

        T** matrix = newMatrix<T>(sz);
        randomMatrix(matrix, sz, static_cast<unsigned>(time(0)), 1, 9);
        long long time_calc = Floyd(matrix, sz);

        std::cout << "    "
                  << std::setw(15) << std::left << sz
                  << std::setw(15) << std::left << time_calc * 1e-9
                  << ops << '\n';

        freeMatrix(matrix, sz);
    }

    std::cout << "=============================================\n\n";
}


template<typename T>
void multiThreadFloydTest(std::vector<size_t>& matrix_sizes, int threads) {
    extern size_t ops;

    std::cout << "\n============ Floyd in " << threads << " threads ============\n";

    std::cout << "    "
              << std::setw(15) << std::left << "Size"
              << std::setw(15) << std::left << "Time (sec)"
              << "Operations\n";

    for (auto& sz : matrix_sizes) {
        ops = 0;

        T** matrix = newMatrix<T>(sz);
        randomMatrix(matrix, sz, static_cast<unsigned>(time(0)), 1, 9);
        long long time_calc = FloydParallel(matrix, sz, threads);

        std::cout << "    "
                  << std::setw(15) << std::left << sz
                  << std::setw(15) << std::left << time_calc * 1e-9
                  << ops << '\n';

        freeMatrix(matrix, sz);
    }

    std::cout << "=============================================\n\n";
}

#endif //_TEST_FLOYD_HPP

