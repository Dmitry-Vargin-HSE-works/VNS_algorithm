#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "usingdata.h"
#include "shaking.h"
#include "localSearch.h"

// vector<vector<int>> - solution object
// example:
// [0] 1 2 1 3 2 2
// [1] 1 1 3 2

void VNS(unsigned long kmax, unsigned long lmax) {
    vector<vector<short>> data = readData();
    unsigned long k = 0;
    vector<vector<short>> best_solution; // = convertDataToStartSolution
    while (k != kmax) {
        //Shaking()
        // vector<vector<int>> local_best = local search
        // if (func(local_best) > func(best_solution))
        //      best_solution = local_best
        ++k;
    }
    writeData(best_solution);
}

int main() {
    srand(time(nullptr));
    /*
    vector<vector<short>> data = readData();
    vector<vector<short>> result = createStartSolution(data.size(), data[0].size());
    for (vector<short> v : result) {
        for (short x : v) {
            cout << x << " ";
        }
        cout << "\n";
    }
    */
    return 0;
}
