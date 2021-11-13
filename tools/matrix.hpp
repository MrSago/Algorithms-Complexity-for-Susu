
#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <random>


template<typename T>
void ReadMatrix(T** m, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cin >> m[i][j];
        }
    }
}


template<typename T>
void PrintMatrix(T** m, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (m[i][j] == int(1e9)) {
                std::cout << "@ ";
            } else {
                std::cout << m[i][j] << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


template<typename T>
T** NewMatrix(size_t N) {
    T** m = new T*[N];
    for (size_t i = 0; i < N; ++i) {
        m[i] = new T[N];
    }
    return m;
}


template<typename T>
void FreeMatrix(T** m, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        delete[] m[i];
    }
    delete[] m;
}


template<typename T>
void RandomMatrix(T** m, size_t N, unsigned seed, int left, int right) {
    std::mt19937 gen(seed);
    std::uniform_int_distribution<T> uid(left, right);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            if (i == j) {
                m[i][j] = 0;
            } else {
                m[i][j] = m[j][i] = uid(gen);
            }
        }
    }
}


template<typename T>
void CopyMatrix(T** m, size_t N, T** out) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            out[i][j] = m[i][j];
        }
    }
}


template<typename T>
T MinElementColumn(T** m, size_t column, size_t N) {
    T min_el = m[0][column];
    for (size_t j = 1; j < N; ++j) {
        min_el = std::min(min_el, m[j][column]);
    }
    return min_el;
}

#endif //_MATRIX_H

