
#include <iostream>
#include <vector>

#include "../algo/commisvoyageur.hpp"
#include "../test/test_commisvoyageur.hpp"


int main () {
    freopen("result.txt", "w", stdout);
    using mytype_t = int;
    std::vector<size_t> brute_force_sizes = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    std::vector<size_t> greedy_sizes = { 1000, 2000, 3000, 5000, 10000,
                                         15000, 20000, 30000, 50000, 100000 };
    std::vector<size_t> bnb_sizes = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

    std::cerr << "Testing started...";

    std::cerr << "\nCommisvoyageur Brute Force...";
    commisvoyageurTest<mytype_t>("Brute Force", commisvoyageurBruteForce, brute_force_sizes);

    std::cerr << "\nCommisvoyageur Gready...";
    commisvoyageurTest<mytype_t>("Greedy", commisvoyageurGreedy, greedy_sizes);

    std::cerr << "\nCommisvoyageur Branch and Bound...";
    commisvoyageurTest<mytype_t>("Branch and Bound", commisvoyageurBranchAndBound, bnb_sizes);

    std::cerr << "\nDone!\n";

    return 0;
}

