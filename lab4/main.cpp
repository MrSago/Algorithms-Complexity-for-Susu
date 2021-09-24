
#include <iostream>
#include <vector>

#include "../algo/commisvoyageur.hpp"
#include "../test/test_commisvoyageur.hpp"


int main () {
    freopen("result.txt", "w", stdout);
    using mytype_t = int8_t;
    std::vector<size_t> brute_force_sizes = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    std::vector<size_t> greedy_sizes = { 1000, 2000, 3000, 5000, 10000,
                                         15000, 20000, 30000, 50000, 100000 };

    std::cerr << "Testing started...\n";

    std::cerr << "Commisvoyageur Brute Force...";
    commisvoyageurTest<mytype_t>("Brute Force", commisvoyageurBrute, brute_force_sizes);

    std::cerr << "\nCommisvoyageur Gready...";
    commisvoyageurTest<mytype_t>("Greedy", commisvoyageurGreedy, greedy_sizes);

    std::cerr << "\nDone!\n";

    return 0;
}

