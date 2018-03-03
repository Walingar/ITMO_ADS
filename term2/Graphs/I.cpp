#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string fileName = "fire";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, m;
unsigned int MAX_N = 20000;
vector<vector<int>> edges(MAX_N);
vector<vector<int>> edgesBack(MAX_N);
vector<int> color(MAX_N, 0);
vector<bool> was(MAX_N, false);
vector<int> component;
vector<int> components(MAX_N, 0);
vector<int> order;
int ans = 0;
vector<int> path(MAX_N, -1);
int start, finish;
int ans1 = 0, ans2 = 0;

void input() {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        edges[x - 1].push_back(y - 1);
        edgesBack[y - 1].push_back(x - 1);
    }
}

void output() {
    //vector<vector<int>> edges((unsigned int) ans);
    vector<bool> stay((unsigned int)ans, true);
    for (int i = 0; i < n; i++)
        for (auto to: edges[i]) {
            if (components[i] != components[to]) {
                if (stay[components[to] - 1]) {
                    stay[components[i] - 1] = false;
                    stay[components[to] - 1] = true;
                } else stay[components[i] - 1] = false;

            }
        }
    for (int i = 0; i < ans; i++) {
        if (stay[i]) ++ans2;
    }
    out << ans2;
}

bool cdfs(int v) {
    was[v] = true;
    component.push_back(v);
    for (auto to: edgesBack[v]) {
        if (!was[to])
            cdfs(to);
    }
}

void dfs(int v) {
    was[v] = true;
    for (auto to: edges[v]) {
        if (!was[to])
            dfs(to);
    }
    order.push_back(v);
    //ans.push_back(v);
}

void solve() {
    for (int i = 0; i < n; ++i)
        if (!was[i])
            dfs(i);
    was.assign(MAX_N, false);
    for (int i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!was[v]) {
            ++ans;
            cdfs(v);
            for (auto j: component) components[j] = ans;
            component.clear();
        }
    }
}

int main() {
    input();
    solve();
    output();
    return 0;
}