
#include <iostream>
#include <chrono>


int main () {
    constexpr size_t cnt = (size_t)10e9;
    constexpr size_t ops = cnt * 3;
    size_t i = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (i < cnt) {
        i = i + 1;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    double t = (stop - start).count() * 1e-9;
    std::cout << "time: " << t << "sec\n";
    std::cout << "ops: " << ops << '\n';
    std::cout << "perfomance: " << ops / t << " ops/sec\n";

    return 0;
}

