#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
 
using namespace std;
 
string fileName = "lca";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n = 1, l, m;
int maxN = 500000 + 50;
int maxM = 500000 + 50;
vector<vector<int> > g;
vector<int> tin, tout;
int timer;
vector<vector<int> > up;
 
vector<vector<int>> edges(maxN);
 
bool upper(int v, int u) {
    return (tin[v] <= tin[u] && tout[v] >= tout[u]);
}
 
 
int lca(int v, int u) {
    if (upper(v, u)) return v;
    if (upper(u, v)) return u;
    for (int i = l; i >= 0; --i)
        if (!upper(up[v][i], u))
            v = up[v][i];
    return up[v][0];
}
 
void dfs(int v, int p = 0) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to: edges[v])
        dfs(to, v);
    tout[v] = ++timer;
}
 
vector<pair<int, int>> req;
 
void input() {
    in >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        in >> s;
        if (s == "ADD") {
            n++;
            int v, u;
            in >> v >> u;
            --v;
            --u;
            edges[v].push_back(u);
        } else {
            int v, u;
            in >> v >> u;
            --v;
            --u;
            req.push_back({v, u});
        }
    }
}
 
void output() {
    for (auto i : req) {
        out << lca(i.first, i.second) + 1 << "\n";
    }
}
 
void solve() {
    tin.resize(n), tout.resize(n), up.resize(n);
    l = 1;
    while ((1 << l) <= n) ++l;
    for (int i = 0; i < n; ++i) up[i].resize(l + 1);
    dfs(0);
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}