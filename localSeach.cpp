#include "localSearch.h"

vector<vector<int>> localSearch(vector<vector<int>> start_solution,
                                vector<vector<int>> best_solution, int lmax) {
  vector<vector<int>> result;
  for (int i = 0; i < start_solution.size(); i++) {
    for (int j = 0; j < start_solution[0].size(); j++) {
      result[i].push_back(start_solution[i][j]);
    }
  }

  // rand() % (b - a + 1) + a
  int l = 1;
  while (l <= lmax) {
    int choice = rand() % 2;
    if (choice == 0) { // moveRow()
      int first_row = rand() % (best_solution[0].size() + 1);
      int second_row = rand() % (best_solution[0].size() + 1);
      if (best_solution[0][first_row] == best_solution[0][second_row]) {
        second_row = rand() % (best_solution[0].size() + 1);
      }
      moveRow(result, first_row, second_row);
    } else { // moveColumns()
      int first_columns = rand() % (best_solution[1].size() + 1);
      int second_columns = rand() % (best_solution[1].size() + 1);
      if (best_solution[0][first_columns] == best_solution[0][second_columns]) {
        second_columns = rand() % (best_solution[1].size() + 1);
      }
      moveColumns(result, first_columns, second_columns);
    }
    ++l;
  }

  return result;
}

double calculateFormula(vector<vector<int>> start_solution,
                        vector<vector<int>> best_solution) {
  int all_num_1 = 0; // number of all 1
  int num_1 = 0; // number of all 1 in clusters
  int num_0 = 0; // number of all 0 in clusters

  for (int i = 0; i < start_solution.size(); i++) {
    int id_cluster = best_solution[0][i];
    for (int j = 0; j < start_solution[0].size(); j++) {
      if (start_solution[i][j] == 1) {
        ++all_num_1;
      }
      if (best_solution[1][j] == id_cluster && start_solution[i][j] == 1) {
        ++num_1;
      } else {
        ++num_0;
      }
    }
  }

  return num_1 / (all_num_1 + num_0);
}

void moveRow (vector<vector<int>> best_solution,
              int first_row, int second_row) {
  int id_cluster = best_solution[0][second_row];
  best_solution[0][second_row] = best_solution[0][first_row];
  best_solution[0][first_row] = id_cluster;
}

void moveColumns(vector<vector<int>> best_solution,
                 int first_columns, int second_columns) {
  int id_cluster = best_solution[1][second_columns];
  best_solution[1][second_columns] = best_solution[1][first_columns];
  best_solution[1][first_columns] = id_cluster;
}