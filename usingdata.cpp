#include "usingdata.h"

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <map>
#include <sstream>

vector<vector<short>> readData() {
    vector<vector<short>> a;
    string path = filesystem::current_path().string();
    path = path.substr(0, path.rfind('/'));
    ifstream input_file(path + "/data/input.txt");
    // cout << path << "/data/input.txt\n\n";
    if (input_file.eof()) {
        cout << "File was not opened!\n";
        throw ;
    }

    string line;
    getline(input_file, line);
    int n = stoi(line.substr(0, line.find(' ')));
    int m = stoi(line.substr(line.find(' '), line.length()));
    for (int i = 0; i < n; ++i) {
        getline(input_file, line);
        auto input_numbers = splitIntString(line);

        vector<short> tmp;
        for (int j = 0; j < m; ++j) {
            tmp.push_back(0);
        }
        for (auto input_number : input_numbers) {
            tmp[input_number-1] = 1;
        }
        a.push_back(tmp);
    }
    input_file.close();
    return a;
}

vector<int> splitIntString(string s) {
    vector<int> v;
    stringstream stream(s);
    string tmp;
    while (getline(stream, tmp, ' ')) {
        v.push_back(stoi(tmp));
    }
    return v;
}

void writeData(vector<vector<int>> solution) {
    string path = filesystem::current_path().string();
    path = path.substr(0, path.rfind('/'));
    ofstream output_file(path + "/data/output.txt");

    for (int m : solution[0]) {
        output_file << m << " ";
    }
    output_file << "\n";
    for (int p : solution[1]) {
        output_file << p << " ";
    }
    output_file << "\n";

    output_file.close();
}
