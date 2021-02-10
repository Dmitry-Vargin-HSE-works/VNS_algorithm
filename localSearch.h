#ifndef VNS_LOCALSEARCH_H
#define VNS_LOCALSEARCH_H

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

double calculateFormula(vector<vector<int>> start_solution,
                        vector<vector<int>> best_solution);
void moveRow (vector<vector<int>> best_solution,
              int first_row, int second_row);
void moveColumns(vector<vector<int>> best_solution,
                 int first_columns, int second_columns);

#endif //VNS_LOCALSEARCH_H
