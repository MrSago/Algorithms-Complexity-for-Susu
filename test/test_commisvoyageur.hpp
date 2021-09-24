
#ifndef _TEST_COMMISVOYAGEUR_HPP
#define _TEST_COMMISVOYAGEUR_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#include "../algo/commisvoyageur.hpp"
#include "../tools/matrix.hpp"


template<typename T>
void commisvoyageurTest(const char algo_name[],
                        commisvoyag_t (*algo_fun)(T**, size_t, size_t),
                        std::vector<size_t>& matrix_sizes) {
    extern size_t ops;

    std::cout << "\n============ Commisvoyageur " << algo_name << " ============\n";

    std::cout << "    "
              << std::setw(15) << std::left << "Size"
              << std::setw(15) << std::left << "Time (sec)"
              << "Operations\n";

    for (auto& sz : matrix_sizes) {
        ops = 0;

        T** matrix = newMatrix<T>(sz);
        randomMatrix(matrix, sz, 0, 1, 99);
        commisvoyag_t res = algo_fun(matrix, sz, 0);

        std::cout << "    "
                  << std::setw(15) << std::left << sz
                  << std::setw(15) << std::left << res.time_calc * 1e-9
                  << ops << '\n';

        freeMatrix(matrix, sz);
    }

    std::cout << "============================" << std::string(strlen(algo_name), '=') << "=============\n\n";
}

#endif //_TEST_COMMISVOYAGEUR_HPP

