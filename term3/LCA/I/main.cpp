#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;
 
string fileName = "tree";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, l, m;
int maxN = 150000 + 50;
map<pair<int, int>, int> wd;
vector<vector<int> > up(maxN);
vector<vector<int> > w(maxN);
vector<vector<int>> edges(maxN);
vector<int> counter;
vector<int> d(maxN);
vector<bool> was(maxN, false);
 
 
int lca(int v, int u) {
    if (d[v] > d[u]) {
        int temp = v;
        v = u;
        u = temp;
    }
    for (int i = l; i >= 0; --i)
        if (d[u] - d[v] >= counter[i])
            u = up[u][i];
    if (v == u)
        return v;
    for (int i = l; i >= 0; --i)
        if (up[v][i] != up[u][i]) {
            v = up[v][i];
            u = up[u][i];
        }
    return up[v][0];
}
 
int depth = 0;
 
void dfs(int v, int p = 0) {
    up[v][0] = p;
    was[v] = true;
    d[v] = depth;
    w[v][0] = wd[{v, p}];
    for (int i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        w[v][i] = w[v][i - 1] + w[up[v][i - 1]][i - 1];
    }
 
    for (auto to: edges[v]) {
        ++depth;
        if (!was[to])
            dfs(to, v);
        --depth;
    }
 
}
 
void input() {
    in >> n;
    for (int i = 1; i < n; ++i) {
        int v, u, weight;
        in >> v >> u >> weight;
        edges[v].push_back(u);
        edges[u].push_back(v);
        wd[{v, u}] = weight;
        wd[{u, v}] = weight;
    }
}
 
int go(int v, int u) {
    int res = 0;
    for (int i = l; i >= 0; --i) {
        if (counter[i] <= d[v] - d[u]) {
            res += w[v][i];
            v = up[v][i];
        }
    }
    return res;
}
 
void output() {
    in >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        in >> v >> u;
        int x = lca(v, u);
        out << go(v, x) + go(u, x) << "\n";
    }
}
 
void solve() {
    l = 1;
    while ((1 << l) <= n) ++l;
    ++l;
    for (int i = 0; i <= l; ++i) counter.push_back(1 << i);
    for (int i = 0; i < n; ++i) up[i].resize(l + 1);
    for (int i = 0; i < n; ++i) w[i].resize(l + 1);
    dfs(0);
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}