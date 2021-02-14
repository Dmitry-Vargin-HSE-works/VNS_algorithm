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
    /*
    for (vector<short> v : data) {
        for (short x : v) {
            cout << x << " ";
        }
        cout << "\n";
    }
    */
    unsigned long k = 0;
    vector<vector<short>> best_solution;
    cout << "Do you want to download last best result?(y/n)\n";
    char message;
    // cin >> message;
    message = 'y';
    if (message == 'y') {
        best_solution = readSolution();
        cout << best_solution[0].size() << " " << best_solution[1].size() << "\n";
        printSolution(data, best_solution);
    } else {
        best_solution = createStartSolution(data.size(), data[0].size());
        cout << best_solution[0].size() << " " << best_solution[1].size() << "\n";
        printSolution(data, best_solution);
    }
    vector<vector<short>> local_best = best_solution;
    while (k < kmax) {
        if (k > 500) {
            local_best = shaking(data, best_solution, lmax);
        }
        // cout << "shaking" << k;
        local_best = localSearch(data, local_best, lmax);
        // cout << " localSearch" << k << "\n";
        if (calculateFormula(data, local_best) > calculateFormula(data, best_solution)) {
            best_solution = local_best;
            //cout << k << "\n";
            writeSolution(data, best_solution);
            k = 0;
        } else {
            ++k;
            // if (k % 500 == 0) cout << calculateFormula(data, local_best) << "\n";
        }
    }
}

int main() {
    srand(time(nullptr));
    /*
    vector<vector<short>> v = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                               {1, 2, 3, 4, 5}};
    for (vector<short> q : v) {
        for (short x : q) {
            cout << x << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    moveRow(v, 1, 2);
    for (vector<short> q : v) {
        for (short x : q) {
            cout << x << " ";
        }
        cout << "\n";
    }
     */
    VNS(1000000, 30);

    return 0;
}
