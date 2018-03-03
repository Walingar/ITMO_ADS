#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
#include <set>
 
using namespace std;
 
string fileName = "lca3";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n = 1, l, m, N;
int const maxN = 50000 + 50;
vector<vector<int>> edges(maxN);
vector<vector<int> > up(maxN);
vector<int> timeIn(maxN), timeOut(maxN);
set<int> roots;
vector<int> d(maxN);
vector<int> counter;
 
void input() {
    in >> N;
    for (int i = 0; i < N; ++i) {
        int v;
        in >> v;
        --v;
        if (v == -1)
            roots.insert(i);
        else
            edges[v].push_back(i);
    }
}
 
int depth = 0;
 
void dfs(int v, int p = 0) {
    up[v][0] = p;
    d[v] = depth;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to: edges[v]) {
        ++depth;
        dfs(to, v);
        --depth;
    }
 
}
 
void merge(int v, int u) {
    depth = d[v];
    dfs(v, up[v][0]);
}
 
int lca(int v, int u) {
    if (up[v][l] != up[u][l])
        return -1;
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
 
void output() {
    in >> m;
    string s;
    int ans = 0, x, y;
    for (int i = 0; i < m; ++i) {
        in >> s >> x >> y;
        int v, u;
        u = (x - 1 + ans) % N;
        v = (y - 1 + ans) % N;
        if (s == "0") {
            ans = lca(u, v) + 1;
            out << ans << "\n";
        } else {
            edges[v].push_back(u);
            merge(v, u);
        }
    }
}
 
 
void solve() {
    l = 1;
    while ((1 << l) <= maxN) ++l;
    ++l;
    for (int i = 0; i <= l; ++i) counter.push_back(1 << i);
    for (int i = 0; i < N; ++i) up[i].resize(l + 1);
    for (auto i: roots) {
        depth = 0;
        dfs(i, i);
    }
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}