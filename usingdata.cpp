#include "usingdata.h"
#include "localSearch.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    const std::string slash="\\";
#else
    const std::string slash="/";
#endif

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
    path = path.substr(0, path.rfind(slash));
    ifstream input_file(path + slash + "data" + slash + "input.txt");
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
        // use it if prefix of strings will be no sorted
        // int index = input_numbers[0];
        input_numbers.erase(input_numbers.begin());
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

vector<vector<short>> readSolution() {
    vector<vector<short>> a;
    vector<short> tmp;
    a.push_back(tmp);
    a.push_back(tmp);
    string path = filesystem::current_path().string();
    path = path.substr(0, path.rfind(slash));
    ifstream input_file(path + slash + "data" + slash + "output.txt");
    if (input_file.eof()) {
        cout << "File was not opened!\n";
        throw ;
    }
    string line;
    for (int i = 0; i < 2; ++i) {
        getline(input_file, line);
        vector<int> vint = splitIntString(line);
        for (int x : vint) {
            a[i].push_back(x);
        }
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

void writeSolution(vector<vector<short>> data, vector<vector<short>> solution) {
    string path = filesystem::current_path().string();
    path = path.substr(0, path.rfind('/'));
    ofstream output_file(path + slash + "data" + slash + "output.txt");

    cout << "New best! " << calculateFormula(data, solution) << "\n";
    for (short m : solution[0]) {
        cout << m << " ";
        output_file << m << " ";
    }
    output_file << "\n";
    cout << "\n";
    for (short p : solution[1]) {
        cout << p << " ";
        output_file << p << " ";
    }
    output_file << "\n";
    cout << "\n\n";

    output_file.close();
}

void printSolution(vector<vector<short>> data, vector<vector<short>> solution) {
    cout << "Your solution:" << calculateFormula(data, solution) << "\n";
    for (short m : solution[0]) {
        cout << m << " ";
    }
    cout << "\n";
    for (short p : solution[1]) {
        cout << p << " ";
    }
    cout << "\n\n";
}
