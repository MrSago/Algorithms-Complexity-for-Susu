
#ifndef _FLOYD_HPP
#define _FLOYD_HPP

#include <chrono>
#include <omp.h>

#include "../matrix.hpp"


long long Floyd(int** w, int N) {
    auto start = std::chrono::high_resolution_clock::now();

    int k, i, j;
    for (k = 0; k < N; ++k) {
        for (i = 0; i < N; ++i) {
            for (j = 0; j < N; ++j) {
                w[i][j] = std::min(w[i][j], w[i][k] + w[k][j]);
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}


long long FloydParallel(int** w, int N, int threads) {
    auto start = std::chrono::high_resolution_clock::now();

    int k, i, j;
    omp_set_num_threads(threads);
#pragma omp parallel for shared(w) private(k, i, j)
    for (k = 0; k < N; ++k) {
        for (i = 0; i < N; ++i) {
            for (j = 0; j < N; ++j) {
                w[i][j] = std::min(w[i][j], w[i][k] + w[k][j]);
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}

#endif //_FLOYD_HPP

