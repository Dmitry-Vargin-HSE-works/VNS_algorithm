#include "localSearch.h"

vector<vector<short>> localSearch(vector<vector<short>> data,
                                vector<vector<short>> solution, unsigned long lmax) {
    // rand() % (b - a + 1) + a
    unsigned long l = 0;
    vector<vector<short>> best_solution = solution;
    int choice;
    short first; short second;
    while (l <= lmax) {
        choice = rand() % 3;
        switch (choice) {
            case 0:
                first = rand() % solution[0].size();
                second = rand() % solution[0].size();
                if (solution[0][first] == solution[0][second]) {
                    ++l;
                    continue;
                }
                solution = moveRow(solution, first, second);
                break;
            case 1:
                first = rand() % solution[1].size();
                second = rand() % solution[1].size();
                if (solution[1][first] == solution[1][second]) {
                    ++l;
                    continue;
                }
                solution = moveColumns(solution, first, second);
                break;

            case 2:
                solution = twoOpt(solution);
                break;

        }

        if (calculateFormula(data, solution) > calculateFormula(data, best_solution)){
            l = 0;
            best_solution = solution;
            // cout << calculateFormula(data, solution) << "\n";
        } else {
            solution = best_solution;
            ++l;
        }
  }

  return best_solution;
}

double calculateFormula(vector<vector<short>> data,
                        vector<vector<short>> solution) {
  int all_num_1 = 0; // number of all 1
  int num_1 = 0; // number of all 1 in clusters
  int num_0 = 0; // number of all 0 in clusters

  for (int i = 0; i < data.size(); i++) {
    int id_cluster = solution[0][i];
    for (int j = 0; j < data[0].size(); j++) {
      if (data[i][j] == 1) {
        ++all_num_1;
      }
      if (solution[1][j] == id_cluster && data[i][j] == 1) {
        ++num_1;
      } else if (solution[1][j] == id_cluster && data[i][j] == 0) {
        ++num_0;
      }
    }
  }

  return num_1 * 1.0 / (all_num_1 + num_0);
}

vector<vector<short>> moveRow (vector<vector<short>> solution,
              short first_row, short second_row) {
  short id_cluster = solution[0][second_row];
  solution[0][second_row] = solution[0][first_row];
  solution[0][first_row] = id_cluster;
    return solution;
}

vector<vector<short>> moveColumns(vector<vector<short>> solution,
                 short first_columns, short second_columns) {
  short id_cluster = solution[1][second_columns];
  solution[1][second_columns] = solution[1][first_columns];
  solution[1][first_columns] = id_cluster;
    return solution;
}

vector<vector<short>> twoOpt (vector<vector<short>> solution) {
    int choice = rand () % 2;
    unsigned int size = solution[choice].size();
    int i1 = 0;
    int i2 = 0;
    unsigned short q = 0;
    while ((i1 == i2) || (abs(i1-i2) > size / 2)) {
        i1 = rand() % size;
        i2 = rand() % size;
        ++q;
        if (q > 100) {
            return solution;
        }
    }
    // i1 must be less then i2
    if (i1 > i2) {
        int tmp = i1;
        i1 = i2;
        i2 = tmp;
    }
    // 2opt
    reverse(solution[choice].begin()+i1, solution[choice].begin()+i2);
    return solution;
}
