#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "usingdata.h"

int main() {
    // readData();
    vector<vector<int>> v = readData();
    for (vector<int> x : v) {
        for (int y : x) {
            cout << y << " ";
        }
        cout << "\n";
    }
    return 0;
}
