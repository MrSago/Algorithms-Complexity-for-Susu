
#ifndef _COMMISVOYAGEUR_HPP
#define _COMMISVOYAGEUR_HPP

#include <vector>
#include <algorithm>
#include <chrono>

#include "../tools/fact.hpp"

struct commisvoyag_s {
    long long time_calc;
    uint64_t sum_path;
    std::vector<size_t> path;
};

static size_t ops = 0;
static constexpr auto fact = precalc_fact<15>();


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
inline T _min_element_col(T** m, size_t i, size_t N) {
    T min_el = m[0][i];
    for (size_t j = 1; j < N; ++j) {
        min_el = min(min_el, ws[j][i]);
    }
    return min_el;
}


template<typename T>
commisvoyag_s commisvoyageurBrute(T** w, size_t N, size_t vert_start) {
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
        uint64_t min_vert = UINT64_MAX;
        size_t save_pos = 0;

        for (size_t j = 0; j < N; ++j) {
            T vert = w[vert_cur][j];
            if (j != vert_cur && !used[j] && vert > 0 &&
                static_cast<uint64_t>(vert) < min_vert) {
                min_vert = static_cast<uint64_t>(vert);
                save_pos = j;
                ops += 12;
            }
            ops += 25;
        }

        if (min_vert == UINT64_MAX) {
            throw std::runtime_error("Path not found!");
        }

        result.sum_path += min_vert;
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
commisvoyag_s commisvoyageurBranchAndBound(T** w, size_t N, size_t vert_start) {
    auto start = std::chrono::high_resolution_clock::now();

    commisvoyag_s result;
    result.sum_path = 0;
    result.path.resize(N - 1);

    T** ws = newMatrix(N);
    for (size_t i = 0; i < N; ++i) {
        memcpy(ws[i], w[i], sizeof(T) * N);
        ws[i][i] = INT_MAX;
    }

    for (size_t k = N ; k > 2; --k) {
        for (size_t i = 0; i < N; ++i) {
            T min_str = *min_element(ws[i], ws[i] + N);
            T min_col = _min_element_col(ws, i, N);

            result.sum_path += static_cast<uint64_t>(min_str + min_col);

            if (min_str > 0) {
                for (size_t j = 0; j < N; ++j) {
                    ws[i][j] -= min_str;
                }
            }
            if (min_col > 0) {
                for (size_t j = 0; j < N; ++j) {
                    ws[j][i] -= min_col;
                }
            }
        }

        T gamilton_value = 0;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (ws[i][j] == 0) {
                    
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_calc = (stop - start).count();

    return result;
}

#endif //_COMMISVOYAGEUR_HPP

