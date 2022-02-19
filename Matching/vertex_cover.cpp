//
// Created by Aigerim Assylkhanova on 19.02.2022.
//


#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m;
    int n;
    cin >> m >> n;
    vector<vector<int>> g(m);

    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int a;
            cin >> a;
            a--;
            g[i].push_back(a);
        }
    }
    vector<int> match(m);
    vector<int> par(n, -1);
    for (int i = 0; i < m; ++i) {
        cin >> match[i];
        match[i]--;
        if (match[i] != -1) {
            par[match[i]] = i;
        }
    }
    vector<bool> used(m);
    vector<bool> rightused(n);
    function<bool(int)> dfs = [&](int v) {
        used[v] = true;
        for (auto x: g[v]) {
            rightused[x] = true;
            if (par[x] == -1 || used[par[x]] == 0 && dfs(par[x])) {
                par[x] = v;
                return true;
            }
        }
        return false;
    };

    for (int i = 0; i < m; ++i) {
        if (match[i] == -1) {
            dfs(i);
        }
    }

    vector<int> leftcover;
    for (int i = 0; i < m; ++i) {
        if (!used[i]) {
            leftcover.push_back(i);
        }
    }
    vector<int> rightcover;
    for (int i = 0; i < n; ++i) {
        if(rightused[i]) {
            rightcover.push_back(i);
        }
    }
    cout << leftcover.size() + rightcover.size() << endl;
    cout << leftcover.size();
    for (auto x: leftcover) {
        cout << " " << x+1;
    }
    cout << endl << rightcover.size();
    for (auto x: rightcover) {
        cout << " " << x+1;
    }
}
