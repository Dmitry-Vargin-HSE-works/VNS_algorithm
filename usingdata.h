#ifndef VNS_USINGDATA_H
#define VNS_USINGDATA_H

#include <iostream>
#include <vector>

using namespace std;

vector<vector<short>> readData();
vector<vector<short>> readSolution();
void writeSolution(vector<vector<short>> data, vector<vector<short>> solution);
void printSolution(vector<vector<short>> data, vector<vector<short>> solution);

vector<int> splitIntString(string s);


#endif //VNS_USINGDATA_H
