
#ifndef _SORT_HPP
#define _SORT_HPP

#include <chrono>

static size_t ops = 0;


template<typename T>
bool _check_sort(T* arr, int sz) {
    for (int i = 1; i < sz; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}


template<typename T>
long long insertionSort(T* arr, int sz) {
    auto start = std::chrono::high_resolution_clock::now();

    ops = 3;
    for (int i = 1; i < sz; ++i) {
        T tmp = arr[i];
        int j = i - 1;
        for (; j >= 0 && arr[j] > tmp; --j) {
            arr[j + 1] = arr[j];
            ops += 6;
        }
        arr[j + 1] = tmp;
        ops += 7;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}


template<typename T>
long long selectionSort(T* arr, int sz) {
    auto start = std::chrono::high_resolution_clock::now();

    ops = 4;
    for (int i = 0; i < sz - 1; ++i) {
        int min_i = i;
        for (int j = i + 1; j < sz; ++j) {
            if (arr[j] < arr[min_i]) {
                min_i = j;
                ops += 2;
            }
            ops += 5;
        }
        if (min_i != i) {
            T tmp = arr[min_i];
            arr[min_i] = arr[i];
            arr[i] = tmp;
            ops += 7;
        }
        ops += 5;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}


template<typename T>
inline int _partition(T* arr, int low, int high) {
    ops += 8;
    T pi = arr[(low + high) / 2];
    for (int i = low, j = high; ; ++i, --j) {
        while (arr[i] < pi) {
            ++i;
            ops += 4;
        }
        while (arr[j] > pi) {
            --j;
            ops += 4;
        }
        if (i >= j) {
            ops += 4;
            return j;
        }
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        ops += 18;
    }
    throw std::runtime_error("Search partition error");
}
template<typename T>
void _recqs(T* arr, int low, int high) {
    while (low < high) {
        int p = _partition(arr, low, high);
        if (p - low < high - p) {
            _recqs(arr, low, p);
            low = p + 1;
        } else {
            _recqs(arr, p + 1, high);
            high = p;
        }
        ops += 15;
    }
    ops += 4;
}
template<typename T>
long long quickSort(T* arr, int sz) {
    ops = 5;
    auto start = std::chrono::high_resolution_clock::now();
    _recqs(arr, 0, sz - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    return (stop - start).count();
}


template<typename T>
inline int _partitionWorst(T* arr, int low, int high) {
    ops += 7;
    T pi = arr[high - 1];
    for (int i = low, j = high; ; ++i, --j) {
        while (arr[i] < pi) {
            ++i;
            ops += 4;
        }
        while (arr[j] > pi) {
            --j;
            ops += 4;
        }
        if (i >= j) {
            ops += 4;
            return j;
        }
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        ops += 18;
    }
    throw std::runtime_error("Search partition error");
}
template<typename T>
void _recqsWorst(T* arr, int low, int high) {
    while (low < high) {
        int p = _partitionWorst(arr, low, high);
        if (p - low < high - p) {
            _recqsWorst(arr, low, p);
            low = p + 1;
        } else {
            _recqsWorst(arr, p + 1, high);
            high = p;
        }
        ops += 15;
    }
    ops += 4;
}
template<typename T>
long long quickSortWorst(T* arr, int sz) {
    ops = 5;
    auto start = std::chrono::high_resolution_clock::now();
    _recqsWorst(arr, 0, sz - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    return (stop - start).count();
}

#endif //_SORT_HPP

