
#include <iostream>
#include <vector>
#include <chrono>

#include "../templ/matrix.hpp"


long long commisvoyageurBrute(int** w, int N, int start = 0) {
    auto start = std::chrono::high_resolution_clock::now();



    auto stop = std::chrono::high_resolution_clock::now();

    return (stop - start).count();
}



int main () {



    return 0;
}