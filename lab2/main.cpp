
#include <iostream>
#include <vector>

#include "../algo/sort.hpp"
#include "../test/test_sort.hpp"


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int64_t;

    std::vector<size_t> arr_sizes = { 1000,  2000,  3500,  6000,  10000,
                                      15000, 20000, 30000, 50000, 100000 };


    std::cerr << "Testing started...";
    StartTestSort<mytype_t>("Insertion Sort", InsertionSort, arr_sizes);
    StartTestSort<mytype_t>("Selection Sort", SelectionSort, arr_sizes);
    std::cerr << "\nDone!";

    return 0;
}

