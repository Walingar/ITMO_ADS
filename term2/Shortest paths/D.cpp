// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <climits>

int n, m, s, f;
const unsigned int MAX_N = 30017;
using namespace std;
ifstream in("pathbgep.in");
ofstream out("pathbgep.out");
int ans = 0;

vector<vector<pair<int, int>>> edges(MAX_N);
set<pair<int, int>> q;

void input() {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int from, to, w;
        in >> from >> to >> w;
        --from;
        --to;
        edges[from].push_back({to, w});
        edges[to].push_back({from, w});
    }
    m *= 2;
}

vector<int> d(MAX_N, INT_MAX);

void solve() {
    s = 0;
    d[s] = 0;
    q.insert({0, s});
    while (!q.empty()) {
        int v = (*q.begin()).second;
        int w = (*q.begin()).first;
        q.erase((*q.begin()));
        if (w != d[v])
            continue;
        if (d[v] == INT_MAX)
            break;
        for (auto to: edges[v])
            if (d[v] + to.second < d[to.first]) {
                d[to.first] = d[v] + to.second;
                q.insert({d[to.first], to.first});
            }
    }
}

void output() {
    for (int f = 0; f < n; ++f) {
        if (d[f] == INT_MAX) d[f] = -1;
        out << d[f] << " ";
    }

}

int main() {
    input();
    solve();
    output();
    return 0;
}