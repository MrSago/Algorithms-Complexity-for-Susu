
#ifndef _FLOYD_TEST_HPP
#define _FLOYD_TEST_HPP

#include <iostream>

#include "Floyd.hpp"
#include "../templ/matrix.hpp"


template<typename T>
void singleThreadFloydTest(int N) {
    long long time;
    T** matrix;

    matrix = newMatrix<T>(N);
    randomMatrix(matrix, N);

    extern size_t ops;
    ops = 0;
    std::cout << "\nFloyd in single thread...";
    time = Floyd(matrix, N);
    std::cout << "\nTime: " << time * 1e-9 << " sec" << '\n';
    std::cout << "Ops: " << ops << '\n';

    freeMatrix(matrix, N);
}


template<typename T>
void multiThreadFloydTest(int N, int threads) {
    long long time;
    T** matrix;

    matrix = newMatrix<T>(N);
    randomMatrix(matrix, N);

    extern size_t ops;
    ops = 0;
    std::cout << "\nFloyd parallel in " << threads << " threads...";
    time = FloydParallel(matrix, N, threads);
    std::cout << "\nTime: " << time * 1e-9 << " sec" << '\n';
    std::cout << "Ops: " << ops << '\n';

    freeMatrix(matrix, N);
}

#endif //_FLOYD_TEST_HPP

