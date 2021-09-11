
#include <iostream>
#include <vector>

#include "../templ/sort.hpp"
#include "../templ/test_sort.hpp"


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int64_t;
    std::vector<size_t> arr_sizes = { 1000, 2000, 3500, 6000, 10000, 15000, 20000, 30000, 50000, 100000 };

    std::cerr << "Testing started...";
    startTestSort<mytype_t>("Insertion Sort", insertionSort, arr_sizes);
    startTestSort<mytype_t>("Selection Sort", selectionSort, arr_sizes);
    std::cerr << "\nDone!";

    return 0;
}

