//
// Created by Aigerim Assylkhanova on 19.02.2022.
//


#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int k;
    cin >> k;
    while (k--) {
        int m, n;
        cin >> m >> n;
        vector<vector<bool>> edge(m, vector<bool>(n));
        vector<vector<int>> g(m);
        for (int i = 0; i < m; ++i) {
            int c;
            cin >> c;
            while (c != 0) {
                edge[i][c - 1] = true;
                cin >> c;
            }
            for (int j = 0; j < n; ++j) {
                if (!edge[i][j]) {
                    g[i].push_back(j);
                }
            }
        }

        vector<bool> used(m);
        vector<int> par(n, -1);
        vector<bool> rused(n);
        function<bool(int)> dfs = [&](int v) {
            used[v] = true;
            for (auto x: g[v]) {
                rused[x] = true;
                if (par[x] == -1 || !used[par[x]] && dfs(par[x])) {
                    par[x] = v;
                    return true;
                }
            }
            return false;
        };

        for (int i = 0; i < m; ++i) {
            used = vector<bool>(m);
            dfs(i);
        }
// п╦я┴п╣п╪ п╬я┌п╨я┐п╢п╟ п╥п╟п©я┐я│п╨п╟я┌я▄я│я▐
        vector<bool> match(m, false);
        for (auto c: par) {
            if (c != -1) {
                match[c] = true;
            }
        }

        rused = vector<bool>(n);
        used = vector<bool>(m);
        for (int i = 0; i < m; ++i) {
            if (!match[i]) {
                dfs(i);
            }
        }

// я│я┤п╦я┌п╟п╣п╪ п╬я┌п╡п╣я┌
        vector<int> leftcover;
        for (int i = 0; i < m; ++i) {
            if (used[i]) {
                leftcover.push_back(i);
            }
        }
        vector<int> rightcover;
        for (int i = 0; i < n; ++i) {
            if (!rused[i]) {
                rightcover.push_back(i);
            }
        }
        cout << leftcover.size() + rightcover.size() << endl;
        cout << leftcover.size() << " " << rightcover.size() << endl;
        for (auto x: leftcover) {
            cout << x + 1 << " ";
        }
        cout << endl;
        for (auto x: rightcover) {
            cout << x + 1 << " ";

        }
        cout << endl;
    }
}


// bipartite, every girl knows every boy and vice versa