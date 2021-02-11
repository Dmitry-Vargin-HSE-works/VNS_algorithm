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
/*1 2 2 1 2
2 1 2 1 1 1 2*/

void VNS(unsigned long kmax, unsigned long lmax) {
    vector<vector<short>> data = readData();
    for (vector<short> v : data) {
        for (short x : v) {
            cout << x << " ";
        }
        cout << "\n";
    }
    unsigned long k = 0;
    vector<vector<short>> best_solution = createStartSolution(data.size(), data[0].size());
    while (k != kmax) {
        vector<vector<short>> local_best = localSearch(data, shaking(data, best_solution, lmax), lmax);
        if (calculateFormula(data, local_best) > calculateFormula(data, best_solution)) {
            best_solution = local_best;
            k = 0;
        } else {
            ++k;
        }
    }
    writeData(data, best_solution);
}

int main() {
    srand(time(nullptr));
    // VNS(1000, 1000);
    vector<vector<short>> data = readData();
    vector<vector<short>> v = createStartSolution(data.size(), data[0].size());
    v = shaking(data, v, 20);
    for (const vector<short>& a : v) {
        for (short x : a) {
            cout << x << " ";
        }
        cout << "\n";
    }
    cout << "Factory num: " << getFactoryNum(v);
    return 0;
}
