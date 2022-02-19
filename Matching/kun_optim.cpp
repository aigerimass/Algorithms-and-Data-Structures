//
// Created by Aigerim Assylkhanova on 19.02.2022.
//


#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    bool one = (a >= b * 2);
    int cost = 0;

    vector<vector<int>> matrix(n, vector<int>(m, -1));
    int left = 0;
    int right = 0;
    vector<vector<int>> g;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == '*') {
                if (one) cost += b;
                else if ((i + j) % 2 == 0) { // п©б╘п©Б∙ёя▐Б■─п©Б∙║п©Б∙÷я▐Б√░ п©Б∙╒п©Б∙╛п©Б∙╘я▐Б√░
                    left++;
                    matrix[i][j] = left - 1;
                    g.emplace_back();
                    // я▐Б■┌п©Б∙╙п©Б∙╛я▐Б■▄я▐Б■─п©Б∙╕п©Б∙╙ п©Б∙║п©Б∙║п©Б∙ёя▐Б■─я▐Б■≤ п©Б∙╕ п©Б∙║п©Б∙╘п©Б∙ёп©Б∙║п©Б∙╛, п©б╘я▐Б■─п©Б∙╛п©Б∙║п©Б∙╛п©Б∙╒п©Б∙╕п©Б∙╙ я▐Б■─п©Б∙ёп©Б∙═я▐Б■─п©Б∙╛
                    if (i > 0 && matrix[i - 1][j] != -1) {
                        g[matrix[i][j]].push_back(matrix[i - 1][j]);
                    }
                    if (j > 0 && matrix[i][j - 1] != -1) {
                        g[matrix[i][j]].push_back(matrix[i][j - 1]);
                    }

                } else { // п©Б∙║я▐Б■▄п©Б∙╛я▐Б■─п©Б∙÷я▐Б√░ п©Б∙╒п©Б∙╛п©Б∙╘я▐Б√░
                    right++;
                    matrix[i][j] = right - 1;
                    // я▐Б■┌п©Б∙╙п©Б∙╛я▐Б■▄я▐Б■─п©Б∙╕п©Б∙╙ п©Б∙║п©Б∙║п©Б∙ёя▐Б■─я▐Б■≤ п©Б∙╕ п©Б∙║п©Б∙╘п©Б∙ёп©Б∙║п©Б∙╛, п©Б∙╛я▐Б■▄я▐Б■▄я▐Б■░п©Б∙╒п©Б∙÷ п©б╘я▐Б■─п©Б∙╛п©Б∙║п©Б∙╛п©Б∙╒п©Б∙╕п©Б∙╙ я▐Б■─п©Б∙ёп©Б∙═я▐Б■─п©Б∙╛
                    if (i > 0 && matrix[i - 1][j] != -1) {
                        g[matrix[i - 1][j]].push_back(matrix[i][j]);
                    }
                    if (j > 0 && matrix[i][j - 1] != -1) {
                        g[matrix[i][j - 1]].push_back(matrix[i][j]);
                    }
                }
            }
        }
    }

    if (one) {
        cout << cost << endl;
        return 0;
    }

// dfs
    vector<bool> used(left);
    vector<int> pair(right, -1);
    vector<bool> free(left, true);
    function<bool(int)> dfs = [&](int v) {
        used[v] = true;
        for (auto x: g[v]) {
            if (pair[x] == -1 || used[pair[x]] == false && dfs(pair[x])) {
                pair[x] = v;
                return true;
            }
        }
        return false;
    };

    for (int run = 1; run;) {
        run = 0;
        used = vector<bool>(left);
        for (int i = 0; i < left; ++i) {
            if (free[i] && dfs(i)) {
                run = 1;
                free[i] = false;
            }
        }
    }
    int count_pair = 0;
    for (auto x: pair) {
        if (x != -1) {
            cost += a;
            count_pair++;
        }
    }
    cout << cost + (right + left - 2 * count_pair) * b << endl;
}

// плитки 1*2, 1*1, минимум деняк на ремонт