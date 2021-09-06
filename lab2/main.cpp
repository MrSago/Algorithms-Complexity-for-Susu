
#include <iostream>

#include "../sort.h"
#include "../test.h"


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int64_t;

    std::cerr << "Testig started...";
    startTest<mytype_t>("Insertion Sort", insertionSort);
    startTest<mytype_t>("Selection Sort", selectionSort);
    //startTest<mytype_t>("Quick Sort", quickSort);
    std::cerr << "\nDone!";

    return 0;
}

