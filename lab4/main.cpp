
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
    std::vector<size_t> ls_sizes = { };

    std::cerr << "Testing started...";
    // CommisvoyageurTest<mytype_t>("Brute Force", CommisvoyageurBruteForce, brute_force_sizes);
    // CommisvoyageurTest<mytype_t>("Greedy", CommisvoyageurGreedy, greedy_sizes);
    // CommisvoyageurTest<mytype_t>("Branch and Bound", CommisvoyageurBranchAndBound, bnb_sizes);
    CommisvoyageurTest<mytype_t>("Local Search", CommisvoyageurLocalSearch, ls_sizes);
    std::cerr << "\nDone!\n";

    return 0;
}

