
#include <iostream>
#include <vector>

#include "../test/test_floyd.hpp"


int main() {
    freopen("result.txt", "w", stdout);
    using mytype_t = int;
    int threads = 4;
    std::vector<size_t> matrix_sizes { 100, 200, 300, 500, 750,
                                       1000, 1500, 2000, 2500, 3000 };

    std::cerr << "Testing started...";
    SingleThreadFloydTest<mytype_t>(matrix_sizes);
    MultiThreadFloydTest<mytype_t>(matrix_sizes, threads);
    std::cerr << "\nDone!\n";

    return 0;
}

