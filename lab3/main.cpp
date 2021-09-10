
#include <iostream>
#include <vector>

#include "../templ/sort.hpp"
#include "../templ/test.hpp"


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int64_t;
    std::vector<size_t> arr_sizes = { 1000000, 1500000,  2000000, 3000000, 5000000, 10000000, 20000000, 30000000, 50000000, 100000000 };
    std::vector<size_t> arr_sizes_worst = { 10000, 15000, 20000, 30000, 50000, 100000, 150000, 200000, 300000, 500000 };

    std::cerr << "Testing started...";
    startTestSort<mytype_t>("Quick Sort (Best-Avarage case)", quickSort, arr_sizes);
    startTestSort<mytype_t>("Quick Sort (Worst case)", quickSortWorst, arr_sizes_worst);
    std::cerr << "\nDone!";

    return 0;
}

