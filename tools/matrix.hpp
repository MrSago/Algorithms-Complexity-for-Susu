
#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <random>


template<typename T>
void readMatrix(T** m, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cin >> m[i][j];
        }
    }
}


template<typename T>
void printMatrix(T** m, size_t N) {
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
T** newMatrix(size_t N) {
    T** m = new T*[N];
    for (size_t i = 0; i < N; ++i) {
        m[i] = new T[N];
    }
    return m;
}


template<typename T>
void freeMatrix(T** m, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        delete[] m[i];
    }
    delete[] m;
}


template<typename T>
void randomMatrix(T** m, size_t N, unsigned seed, int left, int right) {
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

#endif //_MATRIX_H

