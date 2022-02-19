//
// Created by Aigerim Assylkhanova on 19.02.2022.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    int m;
    cin >> n >> m;
    vector<vector<int>> A(n);
    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        while (v!=0) {
            A[i].push_back(v-1);
            cin >> v;
        }
    }
    vector<int> used(n), par(m, -1);
    function<bool(int)> dfs = [&](int v) {
        used[v] = 1;
        for (auto x: A[v]) {
            if (par[x] == -1 || used[par[x]] == 0 && dfs(par[x])) {
                par[x] = v;
                return true;
            }
        }
        return false;
    };
    for (int i = 0; i < n; ++i) {
        used = vector<int>(n, 0);
        dfs(i);
    }
    int count = 0;
    for(int i = 0; i < m; ++i) {
        if (par[i] != -1) {
            count++;
        }
    }
    cout << count << endl;
    for(int i = 0; i < m; ++i) {
        if (par[i] != -1) {
            cout << par[i]+1 << " " << i +1 << endl;
        }
    }

}

