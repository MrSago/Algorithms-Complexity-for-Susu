
#include <iostream>
#include <iomanip>
#include <vector>

#include "../gen.h"
#include "../sort.h"
#include "../test.h"


template<typename T>
void printVector(std::vector<T>& arr) {
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
}


void test_print(test_t t) {
    for (auto& it : t) {
        std::cout << "    " << std::setw(10) << std::left << it.first << static_cast<double>(it.second) * 1e-6 << " ms" << '\n';
    }
    std::cout << '\n';
}


template<typename T>
void runTest(std::string sort_name, long long (*sort_fun)(std::vector<T>&)) {
    std::cout << "\n============ " << sort_name << " ============\n\n";
    std::cout << "Best case (increasing array):\n";
    std::cout << "    " << std::setw(10) << std::left << "Size" << "Time\n";
    test_t test_res = testSort<T>(increasingVector, sort_fun);
    test_print(test_res);

    std::cout << "Avarage case (random array):\n";
    std::cout << "    " << std::setw(10) << "Size" << "Time\n";
    test_res = testSort<T>(randomVector, sort_fun);
    test_print(test_res);

    std::cout << "Worst case (decreasing array):\n";
    std::cout << "    " << std::setw(10) << "Size" << "Time\n";
    test_res = testSort<T>(decreasingVector, sort_fun);
    test_print(test_res);
    std::cout << "========================================\n\n";
}


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int;

    runTest<mytype_t>("Insertion Sort", insertionSort);
    runTest<mytype_t>("Selection Sort", selectionSort);

    return 0;
}

