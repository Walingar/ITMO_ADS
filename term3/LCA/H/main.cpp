#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
 
using namespace std;
 
string fileName = "ancestor";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, l, m;
int maxN = 100000 + 50;
vector<int> tin(maxN), tout(maxN);
int timer = 0;
vector<vector<int> > up(maxN);
int root = 0;
 
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
 
void input() {
    in >> n;
    for (int i = 0; i < n; ++i) {
        int v;
        in >> v;
        if (v == 0)
            root = i;
        else {
            --v;
            edges[v].push_back(i);
        }
    }
}
 
void output() {
    in >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        in >> v >> u;
        int ans = lca(v - 1, u - 1);
        if (upper(v - 1, u - 1))
            out << 1 << "\n";
        else out << 0 << "\n";
    }
}
 
void solve() {
    l = 1;
    while ((1 << l) <= n) ++l;
    ++l;
    for (int i = 0; i < n; ++i) up[i].resize(l + 1);
    dfs(root);
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}