
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <ctime>

#include "../templ/matrix.hpp"


struct commisvoyag_t{
    long long time_ex;
    int sum_path;
    std::vector<int> path;
};


inline int sumPath(int** w, std::vector<int>& perm, int vert_start) {
    int sum_path = 0;
    int cur_vert = vert_start;

    for (auto& it : perm) {
        int tmp = w[cur_vert][it];
        if (tmp <= 0) {
            return INT_MAX;
        }
        sum_path += tmp;
        cur_vert = it;
    }

    int tmp = w[cur_vert][vert_start];
    if (tmp <= 0) {
        return INT_MAX;
    }
    return sum_path + tmp;
}


commisvoyag_t commisvoyageurBrute(int** w, int N, int vert_start = 0) {
    auto start = std::chrono::high_resolution_clock::now();

    commisvoyag_t result;
    result.sum_path = INT_MAX;

    std::vector<int> perm(N - 1);
    for (int i = 0, vert = 0; i < N - 1; ++vert) {
        if (vert != vert_start) {
            perm[i++] = vert;
        }
    }

    do {
        int cur_sum = sumPath(w, perm, vert_start);
        if (cur_sum < result.sum_path) {
            result.sum_path = cur_sum;
            result.path = perm;
        }
    } while (std::next_permutation(perm.begin(), perm.end()));

    if (result.path.size() < N - 2) {
        throw std::runtime_error("Path not found!");
    }

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_ex = (stop - start).count();

    return result;
}


commisvoyag_t commisvoyageurGreedy(int** w, int N, int vert_start = 0) {
    auto start = std::chrono::high_resolution_clock::now();

    commisvoyag_t result;
    result.sum_path = 0;

    std::vector<bool> used(N, false);
    used[vert_start] = true;

    int vert_cur = vert_start;
    for (int i = 0; i < N - 1; ++i) {
        int min_sum = INT_MAX;
        int save_pos = 0;
        for (int j = 0; j < N; ++j) {
            if (j != vert_cur && !used[j] && w[vert_cur][j] > 0 && w[vert_cur][j] < min_sum) {
                min_sum = w[vert_cur][j];
                save_pos = j;
            }
        }
        if (min_sum == INT_MAX) {
            throw std::runtime_error("Path not found!");
        }
        result.sum_path += min_sum;
        result.path.push_back(save_pos);
        used[save_pos] = true;
        vert_cur = save_pos;
    }
    result.sum_path += w[vert_cur][vert_start];

    auto stop = std::chrono::high_resolution_clock::now();
    result.time_ex = (stop - start).count();

    return result;
}


int main () {
    //freopen("result.txt", "w", stdout);
    int N = 5;
    int** matrix = newMatrix<int>(N);
    randomMatrix(matrix, N, time(0));
    printMatrix(matrix, N);

    commisvoyag_t res = commisvoyageurBrute(matrix, N);

    std::cout << res.time_ex * 1e-9 << '\n';
    std::cout << res.sum_path << '\n';
    std::cout << "0 ";
    for (auto& it : res.path) {
        std:: cout << it << ' ';
    }
    std::cout << "0\n";

    return 0;
}

