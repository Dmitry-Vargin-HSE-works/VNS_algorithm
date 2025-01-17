#ifndef VNS_SHAKING_H
#define VNS_SHAKING_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <map>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

// checked
vector<vector<short>> createStartSolution(int m, int p);

vector<vector<short>> shaking(vector<vector<short>> data, vector<vector<short>> solution, unsigned long lmax); // main function

vector<vector<short>> divide(vector<vector<short>> solution, short factory); // divide solution into pieces
vector<vector<short>> merge(vector<vector<short>> solution, short first, short second); // merge them
vector<vector<short>> pull(vector<vector<short>> solution, unsigned long lmax);

// checked
short getFactoryNum(vector<vector<short>> solution);
// short isCorrectSolution(vector<vector<short>> solution);

#endif //VNS_SHAKING_H
