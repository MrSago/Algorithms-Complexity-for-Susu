
#include <iostream>
#include <chrono>
#include <random>
#include <omp.h>


void printMatrix(int** m, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << m[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


int** newMatrix(int N) {
    int** m = new int*[N];
    for (int i = 0; i < N; ++i) {
        m[i] = new int[N];
    }
    return m;
}


void randomMatrix(int** m, int N) {
    std::random_device device {};
    std::mt19937 gen(device());
    std::uniform_int_distribution<int> uid(1, 1000);
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


long long FloydParallel(int** w, int N, int nThreads) {
    auto start = std::chrono::high_resolution_clock::now();

    int k, i, j;
    omp_set_num_threads(nThreads);
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


void freeMatrix(int** m, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] m[i];
    }
    delete[] m;
}


int main() {
    int nThreads, N;
    int** matrix;
    long long time;

    std::cout << "Threads = ";
    std::cin >> nThreads;

    std::cout << "N = ";
    std::cin >> N;

    matrix = newMatrix(N);
    randomMatrix(matrix, N);
    std::cout << "\nFloyd in one thread...";
    time = Floyd(matrix, N);
    std::cout << "\nTime: " << time * 1e-9 << " sec" << '\n';
    freeMatrix(matrix, N);

    matrix = newMatrix(N);
    randomMatrix(matrix, N);
    std::cout << "\nFloyd parallel in " << nThreads << " threads...";
    time = FloydParallel(matrix, N, nThreads);
    std::cout << "\nTime: " << time * 1e-9 << " sec" << '\n';
    freeMatrix(matrix, N);

    return 0;
}

