#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;
 
string fileName = "mail";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, l, m;
int root = 0;
const int maxN = 100000 + 50;
vector<vector<int>> edges(maxN);
vector<int> heavy(maxN, maxN);
vector<int> parent(maxN, -2);
vector<int> parentOfPath(maxN, -2);
vector<int> dist(maxN, -1);
vector<int> where(maxN, -1);
vector<int> h(maxN, -1);
 
class ST {
public:
    ST() {
        size = 0;
    }
 
    int size;
 
    void create() {
        tree.assign(4 * (size + 1), 0);
        build(0, 0, size - 1);
    }
 
    void addVertex(int v) {
        where[v] = size++;
        a.push_back(h[v]);
    }
 
    void add(int v, int value) {
        addToTree(0, 0, size - 1, where[v], value);
    }
 
    int get(int v, int u) {
        return getFromTree(0, 0, size - 1, where[v], where[u]);
    }
 
private:
    vector<int> tree;
    vector<int> a;
 
    void build(int v, int L, int R) {
        if (L == R)
            tree[v] = a[L];
        else {
            int mid = (L + R) / 2;
            build(2 * v + 1, L, mid);
            build(2 * v + 2, mid + 1, R);
            tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
 
    void addToTree(int v, int L, int R, int pos, int value) {
        if (L == R)
            tree[v] = value;
        else {
            int mid = (L + R) / 2;
            if (pos <= mid)
                addToTree(2 * v + 1, L, mid, pos, value);
            else
                addToTree(2 * v + 2, mid + 1, R, pos, value);
            tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
 
    int getFromTree(int v, int L, int R, int l, int r) {
        if (L > r || l > R)
            return 0;
        if (l <= L && R <= r)
            return tree[v];
        int mid = (L + R) / 2;
        return max(getFromTree(2 * v + 1, L, mid, l, r), getFromTree(2 * v + 2, mid + 1, R, l, r));
    }
};
 
vector<ST> d;
vector<int> from(maxN, -1);
 
void input() {
    in >> n;
    for (int i = 0; i < n; ++i) {
        int v;
        in >> v;
        h[i] = v;
    }
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        in >> v >> u;
        --v;
        --u;
        edges[v].push_back(u);
        edges[u].push_back(v);
    }
}
 
 
void add(int v, int h) {
    d[from[v]].add(v, h);
}
 
int get(int v, int u) {
    int ans = -1;
    if (dist[v] > dist[u])
        swap(u, v);
    while (from[u] != from[v]) {
        if (dist[parentOfPath[from[v]]] >= dist[parentOfPath[from[u]]]) {
            ans = max(ans, d[from[v]].get(parentOfPath[from[v]], v));
            v = parent[parentOfPath[from[v]]];
        } else {
            ans = max(ans, d[from[u]].get(parentOfPath[from[u]], u));
            u = parent[parentOfPath[from[u]]];
        }
    }
    if (dist[v] > dist[u])
        swap(u, v);
    return max(ans, d[from[v]].get(v, u));
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
    in >> m;
    string s;
    int v, u;
    for (int i = 0; i < m; ++i) {
        in >> s;
        in >> v >> u;
        --v;
        --u;
        if (s == "!") {
            add(v, u + 1);
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