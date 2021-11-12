
#ifndef _TEST_COMMISVOYAGEUR_HPP
#define _TEST_COMMISVOYAGEUR_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#include "../algo/commisvoyageur.hpp"
#include "../tools/matrix.hpp"


template<typename T>
void CommisvoyageurTest(const char algo_name[],
                        CommisvoyageurResult (*algo_fun)(T**, size_t, size_t),
                        std::vector<size_t>& matrix_sizes) {
    extern size_t ops;

    std::cerr << algo_name << " test...";

    std::cout << "\n============ Commisvoyageur " << algo_name << " ============\n";

    std::cout << "    "
              << std::setw(15) << std::left << "Size"
              << std::setw(15) << std::left << "Time (sec)"
              << "Operations\n";

    for (auto& sz : matrix_sizes) {
        ops = 0;

        T** matrix = NewMatrix<T>(sz);
        RandomMatrix(matrix, sz, 0, 1, 99);
        CommisvoyageurResult res = algo_fun(matrix, sz, 0);

        std::cout << "    "
                  << std::setw(15) << std::left << sz
                  << std::setw(15) << std::left << res.time_calc * 1e-9
                  << ops << '\n';

        FreeMatrix(matrix, sz);
    }

    std::cout << "============================" << std::string(strlen(algo_name), '=') << "=============\n\n";
}

#endif //_TEST_COMMISVOYAGEUR_HPP

