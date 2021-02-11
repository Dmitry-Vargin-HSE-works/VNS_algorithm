#include "shaking.h"
#include "localSearch.h"


vector<vector<short>> createStartSolution(int m, int p) {
    if (m < 1 || p < 1) {
        cout << "createStartSolution\nm < 1 || p < 1\n";
        throw ;
    }
    vector<vector<short>> solution;
    vector<short> v; solution.push_back(v); solution.push_back(v);
    for (int i = 0; i < m; ++i) {
        solution[0].push_back(1);
    }
    for (int i = 0; i < p; ++i) {
        solution[1].push_back(1);
    }
    return solution;
}

vector<vector<short>> shaking(vector<vector<short>> data, vector<vector<short>> solution, unsigned long lmax) {
    const unsigned int max_factory_num = min(data.size(), data[0].size());
    /*
    unsigned int *counter_lines = new unsigned int[factory_num+1];
    unsigned int *counter_columns = new unsigned int [factory_num+1];
    unsigned int *squares = new unsigned int [factory_num+1];
    for (short i : solution[0]) {
        ++counter_lines[i];
    }
    for (short i : solution[1]) {
        ++counter_columns[i];
    }
    for (int i = 1; i < factory_num+1; ++i) {
        squares[i] = counter_lines[i] * counter_columns[i];
    }
    */
    unsigned int factory_num = getFactoryNum(solution);
    if (factory_num < 1) {
        cout << "shaking\nFactory num < 0";
        throw;
    } else if (factory_num == 1 ) {
        divide(solution, 1);
    }
    vector<vector<short>> local_best = solution;
    unsigned long l = 0;
    while (l != lmax){
        if (rand() % 2) {
            solution = merge(solution, rand() % factory_num + 1, rand() % factory_num + 1);
        } else {
            solution = divide(solution, rand() % factory_num + 1);
        }
        if (calculateFormula(data, solution) > calculateFormula(data, local_best)) {
            local_best = solution;
            l = 0;
        } else {
            ++l;
        }
        factory_num = getFactoryNum(solution);
    }
    return local_best;
}

vector<vector<short>> merge(vector<vector<short>> solution, short first, short second) {
    if (first == second)
        return solution;
    else if (first > second) {
        short tmp = first;
        first = second;
        second = tmp;
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < solution[i].size(); ++j) {
            if (solution[i][j] == second) {
                solution[i][j] = first;
            } else if (solution[i][j] > second) {
                --solution[i][j];
            }
        }
    }
    return solution;
}

vector<vector<short>> divide(vector<vector<short>> solution, short factory) {
    // max factory num ==  min length between lines and columns
    if (*max_element(solution[0].begin(), solution[0].end()) == min(solution[0].size(), solution[1].size())) {
        return solution;
    }
    short factory_num = getFactoryNum(solution);
    short second_factory = factory_num + 1;
    short line_counter = 0;
    short max_l = count(solution[0].begin(), solution[0].end(), factory) / 2;
    for (int i = 0; i < solution[0].size(); ++i) {
        if (solution[0][i] == factory) {
            if (line_counter != max_l) {
                solution[0][i] = second_factory;
                ++line_counter;
            } else {
                break;
            }
        }
    }
    line_counter = 0;
    max_l = count(solution[1].begin(), solution[1].end(), factory) / 2;
    for (int i = 0; i < solution[1].size(); ++i) {
        if (solution[1][i] == factory) {
            if (line_counter != max_l) {
                solution[1][i] = second_factory;
                ++line_counter;
            } else {
                break;
            }
        }
    }
    return solution;
}

unsigned short getFactoryNum(vector<vector<short>> solution) {
    sort(solution[0].begin(), solution[0].end());
    solution[0].erase(unique(solution[0].begin(), solution[0].end()), solution[0].end());

    sort(solution[1].begin(), solution[1].end());
    solution[1].erase(unique(solution[1].begin(), solution[1].end()), solution[1].end());

    unsigned short size = solution[0].size();
    for (int i = 0; i < size; ++i) {
        if (solution[0][i] != solution[1][i]) {
            cout << "getFactoryNum\nFactories of lines and columns is not equal\n";
            throw ;
        }
    }
    return solution[0].size();
}

/*
short isCorrectSolution(vector<vector<short>> solution) {
    sort(solution[0].begin(), solution[0].end());
    solution[0].erase(unique(solution[0].begin(), solution[0].end()), solution[0].end());

    sort(solution[1].begin(), solution[1].end());
    solution[1].erase(unique(solution[1].begin(), solution[1].end()), solution[1].end());

    unsigned short size = solution[0].size();
    for (int i = 0; i < size; ++i) {
        if (solution[0][i] != solution[1][i]) {
            // cout << "Factories of lines and columns is not equal\n";
            return -1;
        }
    }
    return solution[0].size();
}
*/
