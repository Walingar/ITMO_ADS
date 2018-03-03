#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string fileName = "points";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, m;
const unsigned int MAX_N = 20000;
vector<vector<pair<int, int>>> edges(MAX_N);
vector<vector<int>> edgesBack(MAX_N);
vector<int> color(MAX_N, 0);
vector<bool> was(MAX_N, false);
vector<int> component;
vector<int> components(MAX_N, 0);
vector<int> order;
int timer, tin[MAX_N], tup[MAX_N];
int ans = 0;
int ans2 = 0;
vector<int> path(MAX_N, -1);
int start, finish;

void input() {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        edges[x - 1].push_back({y - 1, i + 1});
        edges[y - 1].push_back({x - 1, i + 1});
    }
}

void output() {
    out << component.size() << "\n";
    sort(component.begin(), component.end());
    for (auto i: component) out << i << " ";
}

bool cdfs(int v) {
    was[v] = true;
    component.push_back(v);
    for (auto to: edgesBack[v]) {
        if (!was[to])
            cdfs(to);
    }
}

void add(int v) {
    if (find(component.begin(), component.end(), v + 1) == component.end()) component.push_back(v + 1);
}

void dfs(int v, int p) {
    was[v] = true;
    tin[v] = tup[v] = timer++;
    int count = 0;
    for (auto to: edges[v]) {
        if (to.first == p) continue;
        if (was[to.first]) tup[v] = min(tin[to.first], tup[v]);
        else {
            dfs(to.first, v);
            tup[v] = min(tup[to.first], tup[v]);
            if (tup[to.first] >= tin[v] && p != -1) add(v);
            ++count;
        }
    }
    if (p == -1 && count > 1)
        add(v);
}

void solve() {
    timer = 0;
    for (int i = 0; i < n; ++i)
        if (!was[i]) dfs(i, -1);
}


bool check() {
    for (int i = 0; i < n; ++i)
        if (color[i] == 0)
            if (!cdfs(i)) return false;
    return true;
}

int main() {
    input();
    solve();
    output();
    return 0;
}