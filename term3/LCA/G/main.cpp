#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
#include <set>
 
using namespace std;
 
string fileName = "carno";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int l, m, n;
int const maxN = 200000 + 50;
vector<vector<int>> edges(maxN);
vector<bool> dead(maxN, false);
vector<vector<int> > up(maxN);
vector<int> timeIn(maxN), timeOut(maxN);
vector<int> parent(maxN);
vector<int> depth(maxN);
vector<int> counter;
vector<int> r(maxN);
vector<int> alive(maxN);
int timer = 0;
 
void input() {
    in >> n;
}
 
void dfs(int v, int p, int d) {
    up[v][0] = p;
    depth[v] = d;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to: edges[v])
        dfs(to, v, d + 1);
}
 
void makeSet(int v) {
    parent[v] = v;
    r[v] = 0;
}
 
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
 
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (r[a] < r[b]) {
            int temp = a;
            a = b;
            b = temp;
        }
        parent[b] = a;
        if (r[a] == r[b])
            ++r[a];
    }
}
 
void check(int v) {
    makeSet(v);
    for (auto child: edges[v])
        if (dead[child])
            union_sets(child, v);
    alive[find_set(v)] = up[v][0];
    if (dead[up[v][0]]) {
        int temp = alive[find_set(up[v][0])];
        union_sets(v, up[v][0]);
        alive[find_set(v)] = temp;
    }
}
 
int get(int v) {
    if (dead[v])
        return alive[find_set(v)];
    return v;
}
 
int lca(int v, int u) {
    if (depth[v] > depth[u]) {
        int temp = u;
        u = v;
        v = temp;
    }
    for (int i = l; i >= 0; --i)
        if (depth[u] - depth[v] >= counter[i])
            u = up[u][i];
    if (v == u)
        return v;
    for (int i = l; i >= 0; --i)
        if (up[v][i] != up[u][i] && depth[up[v][i]] == depth[up[u][i]]) {
            v = up[v][i];
            u = up[u][i];
        }
    return get(up[v][0]);
}
 
void add(int parent, int child) {
    depth[child] = depth[parent] + 1;
    up[child][0] = parent;
    for (int i = 1; i <= l; ++i) {
        up[child][i] = up[up[child][i - 1]][i - 1];
    }
}
 
void output() {
    string s;
    int numb = 1;
    for (int i = 0; i < n; ++i) {
        in >> s;
        if (s == "+") {
            int v;
            in >> v;
            --v;
            edges[v].push_back(numb);
            add(v, numb);
            numb++;
        } else if (s == "-") {
            int v;
            in >> v;
            --v;
            dead[v] = true;
            check(v);
        } else {
            int v, u;
            in >> v >> u;
            --v;
            --u;
            out << lca(v, u) + 1 << "\n";
        }
    }
}
 
 
void solve() {
    l = 1;
    while ((1 << l) <= n) ++l;
    ++l;
    for (int i = 0; i < maxN; ++i) alive[i] = i;
    for (int i = 0; i <= l; ++i) counter.push_back(1 << i);
    for (int i = 0; i < n; ++i) up[i].resize(l + 1);
    dfs(0, 0, 1);
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}