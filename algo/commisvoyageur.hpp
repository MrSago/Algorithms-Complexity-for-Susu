
#ifndef _COMMISVOYAGEUR_HPP
#define _COMMISVOYAGEUR_HPP

#include <vector>
#include <algorithm>
#include <chrono>

#include "../tools/matrix.hpp"
#include "../tools/fact.hpp"


struct commisvoyag_s {
    long long time_calc;
    uint64_t sum_path;
    std::vector<size_t> path;
};

static size_t ops = 0;
constexpr auto fact = precalc_fact<15>();
constexpr int INF = int(1e9);


template<typename T>
inline uint64_t _len_path(T** w, std::vector<size_t>& perm, size_t vert_start) {
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
commisvoyag_s commisvoyageurBruteForce(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    commisvoyag_s result;
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
        uint64_t cur_sum = _len_path(w, perm, vert_start);
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
commisvoyag_s commisvoyageurGreedy(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    commisvoyag_s result;
    result.sum_path = 0;
    result.path.resize(N - 1);

    std::vector<bool> used(N, false);
    used[vert_start] = true;

    size_t vert_cur = vert_start;
    for (size_t i = 0; i < N - 1; ++i) {
        uint64_t min_weight = UINT64_MAX;
        size_t save_pos = 0;

        for (size_t j = 0; j < N; ++j) {
            T weight = w[vert_cur][j];
            if (j != vert_cur && !used[j] && weight > 0 &&
                static_cast<uint64_t>(weight) < min_weight) {
                min_weight = static_cast<uint64_t>(weight);
                save_pos = j;
                ops += 12;
            }
            ops += 25;
        }

        if (min_weight == UINT64_MAX) {
            throw std::runtime_error("Path not found!");
        }

        result.sum_path += min_weight;
        result.path[i] = save_pos;

        used[save_pos] = true;
        vert_cur = save_pos;
        ops += 18 + i;
    }

    result.sum_path += static_cast<uint64_t>(w[vert_cur][vert_start]);

    ops += 15 + N;

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_calc = (stop - start).count();

    return result;
}


template<typename T>
inline void _copy_matrix(T** m, size_t N, T** out) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            out[i][j] = m[i][j];
        }
    }
}

template<typename T>
inline T _min_element_col(T** m, size_t i, size_t N) {
    T min_el = m[0][i];
    for (size_t j = 1; j < N; ++j) {
        min_el = std::min(min_el, m[j][i]);
    }
    return min_el;
}

template<typename T>
inline uint64_t _reduction_matrix(T** m, size_t N) {
    uint64_t cost = 0;

    for (size_t i = 0; i < N; ++i) {
        T min_str = *std::min_element(m[i], m[i] + N);
        if (min_str > 0 && min_str != INF) {
            cost += static_cast<uint64_t>(min_str);
            for (size_t j = 0; j < N; ++j) {
                if (m[i][j] > 0 && m[i][j] != INF) {
                    m[i][j] -= min_str;
                }
            }
        }
    }

    for (size_t i = 0; i < N; ++i) {
        T min_col = _min_element_col(m, i, N);
        if (min_col > 0 && min_col != INF) {
            cost += static_cast<uint64_t>(min_col);
            for (size_t j = 0; j < N; ++j) {
                if (m[j][i] > 0 && m[j][i] != INF) {
                    m[j][i] -= min_col;
                }
            }
        }
    }

    return cost;
}

template<typename T>
inline void _process_matrix(T** m, size_t N, size_t start, size_t from, size_t to) {
    m[to][start] = INF;
    for (size_t i = 0; i < N; ++i) {
        m[from][i] = m[i][to] = INF;
    }
}

template<typename T>
commisvoyag_s commisvoyageurBranchAndBound(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    commisvoyag_s result;
    result.sum_path = 0;
    result.path.resize(N - 1);

    size_t prev_vert = vert_start;
    std::vector<bool> used(N, false);
    used[prev_vert] = true;

    T** w_cur = newMatrix<T>(N);
    T** w_prev = newMatrix<T>(N);
    _copy_matrix(w, N, w_prev);
    for (size_t i = 0; i < N; ++i) {
        w_prev[i][i] = INF;
    }

    result.sum_path += _reduction_matrix(w_prev, N);

    for (size_t k = 0; k < N - 1; ++k) {
        uint64_t min_cost = UINT64_MAX;
        size_t min_vert = UINT64_MAX;

        for (size_t v = 0; v < N; ++v) {
            if (!used[v]) {
                _copy_matrix(w_prev, N, w_cur);
                _process_matrix(w_cur, N, vert_start, prev_vert, v);
                uint64_t cost = _reduction_matrix(w_cur, N) + w_prev[prev_vert][v];
                if (cost < min_cost) {
                    min_cost = cost;
                    min_vert = v;
                }
            }
        }

        if (min_cost == UINT64_MAX) {
            throw std::runtime_error("Path not found!");
        }

        _process_matrix(w_prev, N, vert_start, prev_vert, min_vert);
        _reduction_matrix(w_prev, N);

        result.path[k] = min_vert;
        result.sum_path += min_cost;

        used[min_vert] = true;
        prev_vert = min_vert;
    }

    freeMatrix(w_cur, N);
    freeMatrix(w_prev, N);

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_calc = (stop - start).count();

    return result;
}

#endif //_COMMISVOYAGEUR_HPP

