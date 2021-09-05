
#ifndef _SORT_H
#define _SORT_H

#include <vector>
#include <chrono>


template<typename T>
bool checkSort(std::vector<T>& arr) {
    for (int i = 1; i < (int)arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}


template<typename T>
long long insertionSort(std::vector<T>& arr) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < (int)arr.size(); ++i) {
        T tmp = arr[i];
        int j = i - 1;
        for (; j >= 0 && arr[j] > tmp; --j) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}


template<typename T>
long long selectionSort(std::vector<T>& arr) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < (int)arr.size() - 1; ++i) {
        int min_i = i;
        for (int j = i + 1; j < (int)arr.size(); ++j) {
            if (arr[j] < arr[min_i]) {
                min_i = j;
            }
        }
        if (min_i != i) {
            std::swap(arr[min_i], arr[i]);
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}

#endif //_SORT_H

