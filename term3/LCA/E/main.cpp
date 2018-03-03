#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
#include <set>
 
using namespace std;
 
string fileName = "dynamic";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
//ofstream out("output.txt");
//ifstream in("input.txt");
int l, m, N;
int const maxN = 100000 + 50;
vector<vector<int>> edges(maxN);
vector<vector<int> > up(maxN);
vector<int> d(maxN);
vector<int> counter;
int root = 0;
int depth = 0;
vector<bool> was(maxN, false);
 
void input() {
    edges.assign(maxN, vector<int>());
    d.assign(maxN, 0);
    up.assign(maxN, vector<int>());
    was.assign(maxN, false);
    root = 0;
    depth = 0;
    for (int i = 0; i < N - 1; ++i) {
        int v, u;
        in >> v >> u;
        --v;
        --u;
        edges[v].push_back(u);
        edges[u].push_back(v);
    }
}
 
void dfs(int v, int p = 0) {
    up[v][0] = p;
    was[v] = true;
    d[v] = depth;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to: edges[v]) {
        ++depth;
        if (!was[to])
            dfs(to, v);
        --depth;
    }
 
}
 
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
 
int answer(int v, int u) {
    int a1 = lca(v, root);
    int a2 = lca(root, u);
    int a3 = lca(v, u);
    int ans = max(d[a1], d[a2]);
    ans = max(ans, d[a3]);
    if (ans == d[a1])
        return a1;
    if (ans == d[a2])
        return a2;
    return a3;
}
 
void output() {
    in >> m;
    string s;
    for (int i = 0; i < m; ++i) {
        in >> s;
        if (s == "!") {
            in >> root;
            --root;
        } else {
            int v, u;
            in >> v >> u;
            --v, --u;
            out << answer(u, v) + 1 << "\n";
        }
    }
}
 
 
void solve() {
    l = 1;
    while ((1 << l) <= maxN) ++l;
    ++l;
    for (int i = 0; i < N; ++i) up[i].resize(l + 1);
    dfs(0);
}
 
 
int main() {
    for (int i = 0; i <= 20; ++i) counter.push_back(1 << i);
    in >> N;
    while (N != 0) {
        input();
        solve();
        output();
        in >> N;
    }
    return 0;
}