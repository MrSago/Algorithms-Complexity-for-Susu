
#ifndef _SORT_HPP
#define _SORT_HPP

#include <chrono>


static size_t ops = 0;


template<typename T>
int __partition(T* arr, size_t low, size_t high) {
    ops += 8;
    T pi = arr[(low + high) / 2];
    for (size_t i = low, j = high; ; ++i, --j) {
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
void __rec_qs(T* arr, size_t low, size_t high) {
    while (low < high) {
        size_t p = __partition(arr, low, high);
        if (p - low < high - p) {
            __rec_qs(arr, low, p);
            low = p + 1;
        } else {
            __rec_qs(arr, p + 1, high);
            high = p;
        }
        ops += 15;
    }
    ops += 4;
}


template<typename T>
int __partition_worst(T* arr, size_t low, size_t high) {
    ops += 7;
    T pi = arr[high - 1];
    for (size_t i = low, j = high; ; ++i, --j) {
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
void __rec_qs_worst(T* arr, size_t low, size_t high) {
    while (low < high) {
        size_t p = __partition_worst(arr, low, high);
        if (p - low < high - p) {
            __rec_qs_worst(arr, low, p);
            low = p + 1;
        } else {
            __rec_qs_worst(arr, p + 1, high);
            high = p;
        }
        ops += 15;
    }
    ops += 4;
}


template<typename T>
bool CheckSort(T* arr, size_t sz) {
    for (size_t i = 1; i < sz; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}


template<typename T>
long long InsertionSort(T* arr, size_t sz) {
    auto start = std::chrono::high_resolution_clock::now();

    ops = 3;
    for (size_t i = 1; i < sz; ++i) {
        T tmp = arr[i];
        size_t j = i - 1;
        for (; j + 1 >= 1 && arr[j] > tmp; --j) {
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
long long SelectionSort(T* arr, size_t sz) {
    auto start = std::chrono::high_resolution_clock::now();

    ops = 4;
    for (size_t i = 0; i < sz - 1; ++i) {
        size_t min_i = i;
        for (size_t j = i + 1; j < sz; ++j) {
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
long long QuickSort(T* arr, size_t sz) {
    ops = 5;
    auto start = std::chrono::high_resolution_clock::now();
    __rec_qs(arr, 0, sz - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    return (stop - start).count();
}


template<typename T>
long long QuickSortWorst(T* arr, size_t sz) {
    ops = 5;
    auto start = std::chrono::high_resolution_clock::now();
    __rec_qs_worst(arr, 0, sz - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    return (stop - start).count();
}

#endif //_SORT_HPP

