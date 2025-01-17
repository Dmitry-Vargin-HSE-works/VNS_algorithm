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
#include <iostream>

using namespace std;

vector<vector<short>> localSearch(vector<vector<short>> data,
                                vector<vector<short>> solution, unsigned long lmax);
double calculateFormula(vector<vector<short>> data,
                        vector<vector<short>> solution);
vector<vector<short>> moveRow (vector<vector<short>> solution,
              short first_row, short second_row);
vector<vector<short>> moveColumns(vector<vector<short>> solution,
                 short first_columns, short second_columns);
vector<vector<short>> twoOpt (vector<vector<short>> solution);

#endif //VNS_LOCALSEARCH_H
