#include "localSearch.h"

vector<vector<short>> localSearch(vector<vector<short>> data,
                                vector<vector<short>> solution, unsigned long lmax) {
    // rand() % (b - a + 1) + a
    unsigned long l = 0;
    vector<vector<short>> best_solution = solution;
    while (l <= lmax) {
        short choice = rand() % 2;
        if (choice == 0) { // moveRow()
          short first_row = rand() % solution[0].size();
          short second_row = rand() % solution[0].size();
          while (solution[0][first_row] == solution[0][second_row]) {
                second_row = rand() % solution[0].size();
          }
          moveRow(solution, first_row, second_row);
        } else { // moveColumns()
          short first_columns = rand() % solution[1].size();
          short second_columns = rand() % solution[1].size();
          while (solution[1][first_columns] == solution[1][second_columns]) {
            second_columns = rand() % solution[1].size();
          }
          moveColumns(solution, first_columns, second_columns);
        }
        if (calculateFormula(data, solution) > calculateFormula(data, best_solution)){
            l = 0;
        } else {
            ++l;
        }
  }

  return solution;
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

void moveRow (vector<vector<short>> solution,
              short first_row, short second_row) {
  short id_cluster = solution[0][second_row];
  solution[0][second_row] = solution[0][first_row];
  solution[0][first_row] = id_cluster;
}

void moveColumns(vector<vector<short>> solution,
                 short first_columns, short second_columns) {
  short id_cluster = solution[1][second_columns];
  solution[1][second_columns] = solution[1][first_columns];
  solution[1][first_columns] = id_cluster;
}