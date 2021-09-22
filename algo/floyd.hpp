
#ifndef _FLOYD_HPP
#define _FLOYD_HPP

#include <chrono>
#include <omp.h>

static size_t ops = 0;


template<typename T>
long long Floyd(T** w, int N) {
    auto start = std::chrono::high_resolution_clock::now();

    int k, i, j;
    ops = 3;
    for (k = 0; k < N; ++k) {
        for (i = 0; i < N; ++i) {
            for (j = 0; j < N; ++j) {
                if (w[i][k] != 0 && w[k][j] != 0) {
                    w[i][j] = std::min(w[i][j], w[i][k] + w[k][j]);
                    ops += 6;
                }
                ops += 12;
            }
            ops += 5;
        }
        ops += 5;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}


template<typename T>
long long FloydParallel(T** w, int N, int threads) {
    auto start = std::chrono::high_resolution_clock::now();

    int k, i, j;
    omp_set_num_threads(threads);
    #pragma omp parallel shared(w) private(k, i, j)
    {
        size_t ops_th = 3;
        #pragma omp for
        for (k = 0; k < N; ++k) {
            for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                    if (w[i][k] != 0 && w[k][j] != 0) {
                        w[i][j] = std::min(w[i][j], w[i][k] + w[k][j]);
                        ops_th += 6;
                    }
                    ops_th += 12;
                }
                ops_th += 5;
            }
            ops_th += 5;
        }
        #pragma omp atomic
        ops += ops_th;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}

#endif //_FLOYD_HPP

