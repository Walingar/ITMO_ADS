#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;
 
string fileName = "minonpath";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, l, m;
int maxN = 50000 + 50;
vector<int> tin, tout;
map<pair<int, int>, int> wd;
int timer;
vector<vector<int> > up;
vector<vector<int> > w;
vector<vector<int>> edges(maxN);
vector<int> counter;
vector<int> d(maxN);
 
bool upper(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}
 
 
int lca(int v, int u) {
    if (upper(v, u)) return v;
    if (upper(u, v)) return u;
    for (int i = l; i >= 0; --i)
        if (!upper(up[v][i], u))
            v = up[v][i];
    return up[v][0];
}
 
int depth = 0;
 
void dfs(int v, int p = 0) {
    tin[v] = ++timer;
    up[v][0] = p;
    w[v][0] = wd[{v, p}];
    d[v] = depth;
    for (int i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        w[v][i] = min(w[v][i - 1], w[up[v][i - 1]][i - 1]);
    }
 
    for (auto to: edges[v]) {
        ++depth;
        dfs(to, v);
        --depth;
    }
 
    tout[v] = ++timer;
}
 
void input() {
    in >> n;
    for (int i = 1; i < n; ++i) {
        int v, weight;
        in >> v >> weight;
        --v;
        edges[v].push_back(i);
        wd[{v, i}] = weight;
        wd[{i, v}] = weight;
    }
}
 
int go(int v, int u) {
    int res = 1000000000;
    for (int i = l; i >= 0; --i) {
        if (counter[i] <= d[v] - d[u]) {
            res = min(res, w[v][i]);
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
        --v;
        --u;
        int x = lca(v, u);
        out << min(go(v, x), go(u, x)) << "\n";
    }
}
 
void solve() {
    tin.resize(n), tout.resize(n), up.resize(n);
    w.resize(n);
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