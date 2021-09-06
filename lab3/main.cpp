
#include <iostream>

#include "../sort.hpp"
#include "../test.hpp"


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int64_t;

    std::cerr << "Testig started...";
    startTestSort<mytype_t>("Quick Sort", quickSort);
    std::cerr << "\nDone!";

    return 0;
}

