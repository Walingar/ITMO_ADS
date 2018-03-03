#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
 
#define in cin
#define out cout
 
using namespace std;
 
//string fileName = "lca";
//ofstream out(fileName + ".out");
//ifstream in(fileName + ".in");
int n, l, m;
int root = 0;
const int maxN = 100000 + 50;
vector<vector<int>> edges(maxN);
vector<int> heavy(maxN, maxN);
vector<int> parent(maxN, -2);
vector<int> parentOfPath(maxN, -2);
vector<int> dist(maxN, -1);
vector<int> where(maxN, -1);
 
class ST {
public:
    ST() {
        size = 0;
    }
 
    int size;
 
    void create() {
        tree.assign(4 * (size + 1), 0);
    }
 
    void addVertex(int v) {
        where[v] = size++;
    }
 
    void add(int v, int u, int value) {
        int l = where[v];
        int r = where[u];
        addToTree(0, 0, size, l, r, value);
    }
 
    int get(int v, int u) {
        return getFromTree(0, 0, size, where[v], where[u]);
    }
 
private:
    vector<int> tree;
 
    void addToTree(int v, int L, int R, int l, int r, int value) {
        if (L > r || R <= l)
            return;
        if (L + 1 == R)
            tree[v] += value;
        else if (l < L && R < r)
            tree[v] += value;
        else {
            int mid = (L + R) / 2;
            addToTree(v * 2 + 1, L, mid, l, r, value);
            addToTree(v * 2 + 2, mid, R, l, r, value);
        }
    }
 
    int getFromTree(int v, int L, int R, int l, int r) {
        if (L > r || R <= l)
            return 0;
        if (L + 1 == R)
            return tree[v];
        else if (l < L && R < r)
            return tree[v];
        else {
            int mid = (L + R) / 2;
            return tree[v] +
                   getFromTree(v * 2 + 1, L, mid, l, r) +
                   getFromTree(v * 2 + 2, mid, R, l, r);
        }
    }
};
 
vector<ST> d;
vector<int> from(maxN, -1);
 
void input() {
    in >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        in >> v >> u;
        --v;
        --u;
        edges[v].push_back(u);
        edges[u].push_back(v);
    }
}
 
 
void add(int v, int u) {
    if (dist[v] > dist[u])
        swap(u, v);
    while (from[u] != from[v]) {
        if (dist[parentOfPath[from[v]]] >= dist[parentOfPath[from[u]]]) {
            d[from[v]].add(parentOfPath[from[v]], v, 1);
            v = parent[parentOfPath[from[v]]];
        } else {
            d[from[u]].add(parentOfPath[from[u]], u, 1);
            u = parent[parentOfPath[from[u]]];
        }
    }
    if (dist[v] > dist[u])
        swap(u, v);
    d[from[v]].add(heavy[v], u, 1);
}
 
int get(int v, int u) {
    if (dist[v] < dist[u])
        swap(u, v);
    return d[from[v]].get(v, v);
}
 
vector<int> used(maxN, false);
vector<int> w(maxN, 1);
 
void dfsCount(int v, int p = 0, int h = 1) {
    dist[v] = h;
    parent[v] = p;
    used[v] = true;
    int maxW = -1;
    for (auto to: edges[v])
        if (!used[to]) {
            dfsCount(to, v, h + 1);
            w[v] += w[to];
            if (w[to] > maxW) {
                maxW = w[to];
                heavy[v] = to;
            }
        }
}
 
void dfsGetHLD(int v, int p = -1) {
    if (p == -1) {
        ST tree;
        d.push_back(tree);
        int size = (int) d.size() - 1;
        parentOfPath[size] = v;
        from[v] = size;
        d[size].addVertex(v);
    } else {
        d[p].addVertex(v);
        from[v] = p;
    }
    used[v] = true;
    for (auto to: edges[v])
        if (!used[to]) {
            if (heavy[v] == to)
                dfsGetHLD(to, from[v]);
            else
                dfsGetHLD(to);
        }
}
 
void solve() {
    dfsCount(root);
    used.assign(maxN, false);
    w.clear();
    dfsGetHLD(root);
    for (auto &tree: d)
        tree.create();
}
 
void output() {
    string s;
    int v, u;
    for (int i = 0; i < m; ++i) {
        in >> s;
        in >> v >> u;
        --v;
        --u;
        if (s == "P") {
            add(v, u);
        } else {
            out << get(v, u) << "\n";
        }
    }
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}