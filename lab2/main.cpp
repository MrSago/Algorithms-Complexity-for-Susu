
#include <iostream>

#include "../templ/sort.hpp"
#include "../templ/test.hpp"


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int64_t;

    std::cerr << "Testig started...";
    startTestSort<mytype_t>("Insertion Sort", insertionSort);
    startTestSort<mytype_t>("Selection Sort", selectionSort);
    std::cerr << "\nDone!";

    return 0;
}

