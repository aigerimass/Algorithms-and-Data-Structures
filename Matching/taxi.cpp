//
// Created by Aigerim Assylkhanova on 19.02.2022.
//


#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct point {
    int x;
    int y;

    int time_to(point to) {
        return abs(x - to.x) + abs(y - to.y);
    }
};

struct q {
    point from;
    int t = 0;
    point to;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m;
    cin >> m;
    vector<vector<int>> g(m);
    vector<q> ver(m);
    for (int i = 0; i < m; ++i) {
        char c;
        int t;
        cin >> t >> c;
        t *= 60;
        int mi;
        cin >> mi >>
            ver[i].from.x >> ver[i].from.y >>
            ver[i].to.x >> ver[i].to.y;
        ver[i].t = t + mi;
        // п©я─п╬п╡п╣п╢п╣п╪ я─п╣п╠я─п╟
        for (int j = 0; j < i; ++j) {
            if (ver[i].t > ver[j].t + ver[j].from.time_to(ver[j].to) +
                           ver[j].to.time_to(ver[i].from)) {
//                cout << " i am h e r e " << endl;
                g[j].push_back(i);
            }
        }
    }
//    for (int i = 0; i < m; ++i) {
//        cout << i << " ";
//        for (auto x: g[i]) {
//            cout << x << " ";
//
//        }
//        cout << endl;
//    }
    // я─п╟п╥п╢п╡п╬п╦п╩п╦ пЁя─п╟я└ я┌п╦п©п╟
    vector<bool> used(m);
    vector<int> par(m, -1);
    function<bool(int)> dfs = [&](int v) {
        used[v] = true;
        for (auto x: g[v]) {
            if (par[x] == -1 || !used[par[x]] && dfs(par[x])) {
                par[x] = v;
                return true;
            }
        }
        return false;
    };

    for (int i = 0; i < m; ++i) {
        if (dfs(i)) {
            used = vector<bool>(m);
        }
    }
    int count = 0;
    for (auto x: par) {
        if (x != -1) {
            count++;
        }
    }
    cout << m - count << endl;
}

// ацикличный граф, покрытие цепями и Дилворт. мин кол-во машин
// для всех заказов