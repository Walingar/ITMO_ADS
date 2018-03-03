#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
 
using namespace std;
 
string fileName = "lca_rmq";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n = 1, l, m, N;
int const maxN = 100000 + 50;
int const maxM = 10000000 + 50;
vector<int> depth(maxN);
vector<vector<int>> edges(maxN);
vector<int> order;
vector<int> first(maxN, -1);
int const maxLog = 20;
int sparse[2 * maxN][2 * maxLog];
int pows[2 * maxLog];
int lens[2 * maxN];
 
void input() {
    in >> N >> m;
    for (int i = 1; i < N; ++i) {
        int v;
        in >> v;
        edges[v].push_back(i);
    }
}
 
 
void dfs(int v, int p) {
    depth[v] = p;
    order.push_back(v);
    for (auto to: edges[v]) {
        dfs(to, p + 1);
        order.push_back(v);
    }
}
 
int mins(int v, int u) {
    return depth[v] < depth[u] ? v : u;
}
 
int getAnswer(int left, int right) {
    int j = lens[right - left + 1];
    return mins(sparse[left][j], sparse[right - pows[j] + 1][j]);
}
 
int lca(int v, int u) {
    v = first[v];
    u = first[u];
    if (u < v) {
        int temp = u;
        u = v;
        v = temp;
    }
    //out << " " << v << " " << u;
    return getAnswer(v, u);
}
 
long long a1, a2, x, y, z;
 
void outSparse() {
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n - pows[i]; ++j)
            out << sparse[j][i] << " ";
        out << "\n";
    }
 
}
 
void output() {
    //outSparse();
    in >> a1 >> a2;
    in >> x >> y >> z;
    int v = 0;
    long long ai, aj;
    long long s = 0;
    for (int i = 1; i <= m; ++i) {
        //out << (a1 + v) % N << " " << a2;
        v = lca((a1 + v) % N, a2);
        //out << " " << v << "\n";
        s += v;
        ai = (x * a1 + y * a2 + z) % N;
        aj = (x * a2 + y * ai + z) % N;
        a1 = ai;
        a2 = aj;
    }
    out << s;
}
 
 
int fl(int len) {
    if (len == 1)
        return 0;
    else
        return fl(len / 2) + 1;
}
 
 
void solve() {
    dfs(0, 1);
    for (int i = 0; i < order.size(); ++i) {
        int v = order[i];
        if (first[v] == -1)
            first[v] = i;
    }
    n = order.size();
    l = (int) (log(n) / log(2)) + 1;
    for (int i = 0; i <= l; ++i)
        pows[i] = 1 << i;
    for (int i = 1; i <= n; ++i)
        lens[i] = fl(i);
 
    for (int i = 0; i < l; ++i)
        for (int j = 0; j < n - pows[i]; ++j)
            if (i == 0)
                sparse[j][i] = order[j];
            else
                sparse[j][i] = mins(sparse[j][i - 1], sparse[j + pows[i - 1]][i - 1]);
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}