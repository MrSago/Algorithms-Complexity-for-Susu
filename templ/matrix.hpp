
#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <random>


template<typename T>
void printMatrix(T** m, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << m[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


template<typename T>
T** newMatrix(int N) {
    T** m = new T*[N];
    for (int i = 0; i < N; ++i) {
        m[i] = new T[N];
    }
    return m;
}


template<typename T>
void freeMatrix(T** m, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] m[i];
    }
    delete[] m;
}


template<typename T>
void randomMatrix(T** m, int N) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<T> uid(1, 1000);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == j) {
                m[i][j] = 0;
            } else {
                m[i][j] = m[j][i] = uid(gen);
            }
        }
    }
}

#endif //_MATRIX_H

