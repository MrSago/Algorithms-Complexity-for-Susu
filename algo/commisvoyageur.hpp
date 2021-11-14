
#ifndef _COMMISVOYAGEUR_HPP
#define _COMMISVOYAGEUR_HPP

#include <algorithm>
#include <chrono>
#include <vector>

#include "../tools/fact.hpp"
#include "../tools/matrix.hpp"


struct CommisvoyageurResult {
    long long time_calc;
    uint64_t sum_path;
    std::vector<size_t> path;
};

static size_t ops = 0;
constexpr auto fact = PrecalcFact<15>();
constexpr int INF = int(1e9);


template<typename T>
uint64_t __len_path(T** w, std::vector<size_t>& perm, size_t vert_start) {
    uint64_t sum_path = 0;
    size_t cur_vert = vert_start;

    for (auto& it : perm) {
        T tmp = w[cur_vert][it];
        if (tmp <= 0) {
            return UINT64_MAX;
        }
        sum_path += static_cast<uint64_t>(tmp);
        cur_vert = it;
        ops += 13;
    }

    T tmp = w[cur_vert][vert_start];
    if (tmp <= 0) {
        return UINT64_MAX;
    }

    ops += 13;
    return sum_path + static_cast<uint64_t>(tmp);
}


template<typename T>
uint64_t __reduction_matrix(T** m, size_t N) {
    uint64_t cost = 0;

    for (size_t i = 0; i < N; ++i) {
        T min_str = *std::min_element(m[i], m[i] + N);
        if (min_str > 0 && min_str != INF) {
            cost += static_cast<uint64_t>(min_str);
            for (size_t j = 0; j < N; ++j) {
                if (m[i][j] > 0 && m[i][j] != INF) {
                    m[i][j] -= min_str;
                    ops += 6;
                }
                ops += 9;
            }
            ops += 7;
        }
        ops += N;
    }

    for (size_t i = 0; i < N; ++i) {
        T min_col = MinElementColumn(m, i, N);
        if (min_col > 0 && min_col != INF) {
            cost += static_cast<uint64_t>(min_col);
            for (size_t j = 0; j < N; ++j) {
                if (m[j][i] > 0 && m[j][i] != INF) {
                    m[j][i] -= min_col;
                    ops += 6;
                }
                ops += 9;
            }
            ops += 7;
        }
        ops += N;
    }

    ops += 5;
    return cost;
}


template<typename T>
void __prepare_matrix(T** m, size_t N, size_t start, size_t from, size_t to) {
    m[to][start] = INF;
    for (size_t i = 0; i < N; ++i) {
        m[from][i] = m[i][to] = INF;
        ops += 8;
    }
    ops += 5;
}


template<typename T>
CommisvoyageurResult CommisvoyageurBruteForce(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    CommisvoyageurResult result;
    result.sum_path = UINT64_MAX;

    std::vector<size_t> perm(N - 1);
    for (size_t i = 0, vert = 0; i < N - 1; ++vert) {
        if (vert != vert_start) {
            perm[i++] = vert;
            ops += 6;
        }
        ops += 7;
    }
    ops += 12 + (N - 1) * 2;

    do {
        uint64_t cur_sum = __len_path(w, perm, vert_start);
        if (cur_sum < result.sum_path) {
            result.sum_path = cur_sum;
            result.path = perm;
        }
        ops += 12 + N * N;
    } while (std::next_permutation(perm.begin(), perm.end()));
    ops += 3 + fact.arr[N + 1];

    if (result.path.size() < N - 2) {
        throw std::runtime_error("Path not found!");
    }

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_calc = (stop - start).count();

    return result;
}


template<typename T>
CommisvoyageurResult CommisvoyageurGreedy(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    CommisvoyageurResult result;
    result.sum_path = 0;
    result.path.resize(N - 1);

    std::vector<bool> used(N, false);
    used[vert_start] = true;

    size_t vert_cur = vert_start;
    for (size_t i = 0; i < N - 1; ++i) {
        uint64_t weight_min = UINT64_MAX;
        size_t save_pos = 0;

        for (size_t j = 0; j < N; ++j) {
            uint64_t weight = static_cast<uint64_t>(w[vert_cur][j]);
            if (j != vert_cur && !used[j] && weight > 0 && weight < weight_min) {
                weight_min = weight;
                save_pos = j;
                ops += 12;
            }
            ops += 25;
        }

        if (weight_min == UINT64_MAX) {
            throw std::runtime_error("Path not found!");
        }

        result.sum_path += weight_min;
        result.path[i] = save_pos;

        used[save_pos] = true;
        vert_cur = save_pos;
        ops += 18 + i;
    }
    ops += 15 + N;

    result.sum_path += static_cast<uint64_t>(w[vert_cur][vert_start]);

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_calc = (stop - start).count();

    return result;
}


template<typename T>
CommisvoyageurResult CommisvoyageurBranchAndBound(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    CommisvoyageurResult result;
    result.sum_path = 0;
    result.path.resize(N - 1);
    ops += N + 4;

    size_t vert_prev = vert_start;
    std::vector<bool> used(N, false);
    used[vert_prev] = true;
    ops += N + 5;

    T** w_save_false = NewMatrix<T>(N);
    T** w_save_true = NewMatrix<T>(N);
    T** w_cur = w_save_true;
    bool current_matrix = true;
    ops += 2 * N * N + 9;

    T** w_prev = NewMatrix<T>(N);
    CopyMatrix(w, N, w_prev);
    for (size_t i = 0; i < N; ++i) {
        w_prev[i][i] = INF;
    }
    ops += 2 * N * N + N;

    result.sum_path += __reduction_matrix(w_prev, N);

    for (size_t k = 0; k < N - 1; ++k) {
        uint64_t cost_min = UINT64_MAX;
        size_t vert_min = SIZE_MAX;

        for (size_t vert_cur = 0; vert_cur < N; ++vert_cur) {
            if (!used[vert_cur]) {
                CopyMatrix(w_prev, N, w_cur);
                __prepare_matrix(w_cur, N, vert_start, vert_prev, vert_cur);
                uint64_t cost = __reduction_matrix(w_cur, N) + w_prev[vert_prev][vert_cur];
                if (cost < cost_min) {
                    cost_min = cost;
                    vert_min = vert_cur;
                    w_cur = current_matrix ? w_save_false : w_save_true;
                    current_matrix = !current_matrix;
                    ops += 5;
                }
                ops += N * N;
            }
            ops += 4;
        }

        if (cost_min == UINT64_MAX) {
            throw std::runtime_error("Path not found!");
        }

        if (current_matrix) {
            std::swap(w_prev, w_save_false);
        } else {
            std::swap(w_prev, w_save_true);
        }

        used[vert_min] = true;
        vert_prev = vert_min;

        result.path[k] = vert_min;
        result.sum_path += cost_min;
        ops += 17;
    }
    ops += 5;

    FreeMatrix(w_save_true, N);
    FreeMatrix(w_save_false, N);
    FreeMatrix(w_prev, N);
    ops += 3 * N * N;

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_calc = (stop - start).count();

    return result;
}


template<typename T>
CommisvoyageurResult CommisvoyageurLocalSearch(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    CommisvoyageurResult result;
    result.sum_path = 0;
    result.path.resize(N - 1);

    //

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_calc = (stop - start).count();

    return result;
}


#endif //_COMMISVOYAGEUR_HPP

