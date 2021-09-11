
#include <iostream>

#include "FloydTest.hpp"


int main() {
    using mytype_t = int;
    int threads, N;
    
    std::cout << "Threads = ";
    std::cin >> threads;

    std::cout << "N = ";
    std::cin >> N;

    singleThreadFloydTest<mytype_t>(N);
    multiThreadFloydTest<mytype_t>(N, threads);

    return 0;
}

