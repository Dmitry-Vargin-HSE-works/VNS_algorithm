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
        printSolution(data, best_solution);
    } else {
        best_solution = createStartSolution(data.size(), data[0].size());
        printSolution(data, best_solution);
    }
    while (k != kmax) {
        vector<vector<short>> local_best = shaking(data, best_solution, lmax);
        // cout << "shaking" << k;
        local_best = localSearch(data, shaking(data, best_solution, lmax), lmax);
        // cout << " localSearch" << k << "\n";
        if (calculateFormula(data, local_best) > calculateFormula(data, best_solution)) {
            best_solution = local_best;
            cout << k << "\n";
            writeSolution(data, best_solution);
            k = 0;
        } else {
            ++k;
        }
    }
}

vector<vector<short>> twoOpt (vector<vector<short>> solution) {
  int index = 1;
  int choice = rand () % 2;
  while (solution[choice][index - 1] == solution[choice][index + 1]) {
    index = rand() % ((solution[choice].size() - 2) - 1 + 1) + 1;
  }
  int x = solution[choice][index - 1];
  solution[choice][index - 1] = solution[choice][index + 1];
  solution[choice][index + 1] = x;

  return solution;
}

int main() {
    srand(time(nullptr));

    vector<vector<short>> solution {{1, 1, 2, 3, 3},
                                    {1, 1, 1, 3, 3, 2, 2}};

    for (vector<short> v : solution) {
      for (short x : v)
        cout << x << " ";
      cout << endl;
    }

    while (true) {
      cout << "New!\n";
      for (vector<short> v : twoOpt(solution)) {
        for (short x : v)
          cout << x << " ";
        cout << endl;
      }
    }

    return 0;
}
