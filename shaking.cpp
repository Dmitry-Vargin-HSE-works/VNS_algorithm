#include "shaking.h"
#include "localSearch.h"
#include "usingdata.h"

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
    vector<vector<short>> tmp_solution;
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
    short line_size = data.size();
    short column_size = data[0].size();
    unsigned long l = 0;
    short rindex1 = 0, rindex2 = 0;
    switch (rand() % 2) {
        case 0:
            lmax = lmax / 4;
            while (l != lmax) {

                rindex1 = rand() % line_size;
                switch (rand() % 3) {
                    case 0:
                        rindex2 = rand() % line_size;
                        if (rindex1 == rindex2) {
                            ++l;
                            continue;
                        }
                        solution = merge(solution, solution[0][rindex1], solution[0][rindex2]);
                        break;
                    case 1:
                        tmp_solution = divide(solution, solution[0][rindex1]);
                        if (getFactoryNum(tmp_solution) == -1) {
                            continue;
                        } else {
                            solution = tmp_solution;
                        }
                        break;
                }
                ++l;
                // factory_num = getFactoryNum(solution);
            }
        case 1:
            solution = pull(solution, lmax);
            //printSolution(data, solution);
            break;
    }
    return solution;
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

    for (int q = 0; q < 2; ++q) {
        for (int i = 0; i < solution[0].size(); ++i) {
            if (solution[q][i] == factory) {
                solution[q][i] = rand() % 2 ? second_factory : solution[q][i];
            }
        }
    }
    return solution;
}

vector<vector<short>> pull(vector<vector<short>> solution, unsigned long lmax) {
    vector<short> tmp;
    vector<vector<short>> pull = {tmp, tmp};
    unsigned short l_len = solution[0].size();
    unsigned short c_len = solution[1].size();
    unsigned short r;
    unsigned short tmp_size = l_len;
    while (tmp_size > l_len / 4) {
        r = rand() % tmp_size;

        pull[0].push_back(solution[0][r]);
        solution[0].erase(solution[0].begin() + r);

        tmp_size = solution[0].size();
    }
    tmp_size = c_len;
    while (tmp_size > c_len / 4) {
        r = rand() % tmp_size;

        pull[1].push_back(solution[1][r]);
        solution[1].erase(solution[1].begin() + r);

        tmp_size = solution[1].size();
    }
    solution[0].insert(solution[0].end(), pull[0].begin(), pull[0].end());
    solution[1].insert(solution[1].end(), pull[1].begin(), pull[1].end());
    return solution;
}

short getFactoryNum(vector<vector<short>> solution) {
    sort(solution[0].begin(), solution[0].end());
    solution[0].erase(unique(solution[0].begin(), solution[0].end()), solution[0].end());

    sort(solution[1].begin(), solution[1].end());
    solution[1].erase(unique(solution[1].begin(), solution[1].end()), solution[1].end());

    unsigned short size = solution[0].size();
    for (int i = 0; i < size; ++i) {
        if (solution[0][i] != solution[1][i]) {
            // cout << "getFactoryNum\nFactories of lines and columns is not equal\n";
            return -1;
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
