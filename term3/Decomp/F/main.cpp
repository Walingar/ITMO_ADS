#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
 
using namespace std;
 
#define in cin
#define out cout
 
//ifstream in("mail.in");
//ofstream out("mail.out");
 
long long n, m;
long long MAX_N = 2 * 100000 + 50;
vector<vector<long long> > edges(MAX_N);
vector<long long> centroidDecomp(MAX_N);
vector<vector<long long>> centroidArrays(MAX_N);;
vector<long long> level(MAX_N, -1);
vector<unordered_map<long long, long long>> d(MAX_N);
vector<long long> sizeWhite(MAX_N, 0);
vector<long long> sizeBlack(MAX_N, -1);
vector<long long> white(MAX_N, 0);
vector<long long> black(MAX_N, -1);
vector<unordered_map<long long, long long>> whiteArray(MAX_N);
vector<unordered_map<long long, long long>> blackArray(MAX_N);
vector<bool> color(MAX_N, false);
vector<bool> deleted(MAX_N, false);
 
 
void input() {
    in >> n >> m;
    long long v, u;
    for (long long i = 0; i < n - 1; ++i) {
        in >> v >> u;
        --v;
        --u;
        edges[v].push_back(u);
        edges[u].push_back(v);
    }
}
 
long long dfsCounting(long long v, long long size, long long &centroid, long long p = -1) {
    long long s = 1;
    for (auto to: edges[v])
        if (level[to] == -1 && to != p)
            s += dfsCounting(to, size, centroid, v);
    if (centroid == -1 && (2 * s >= size || p == -1))
        centroid = v;
    return s;
}
 
void dfsCreate(long long v, long long p, long long depth, long long centroid) {
    d[centroid][v] = depth;
    sizeBlack[centroid]++;
    black[centroid] += depth;
    centroidArrays[centroid].push_back(v);
    for (auto to: edges[v])
        if (!deleted[to] && to != p)
            dfsCreate(to, v, depth + 1, centroid);
}
 
void dfs(long long v, long long size, long long depth, long long last) {
    long long centroid = -1;
    dfsCounting(v, size, centroid);
    level[centroid] = depth;
    centroidDecomp[centroid] = last;
    black[centroid] = 0;
    sizeBlack[centroid] = 0;
    deleted[centroid] = true;
 
    dfsCreate(centroid, -1, 0, centroid);
 
    for (auto to: edges[centroid]) {
        if (level[to] == -1)
            dfs(to, size / 2, depth + 1, centroid);
    }
}
 
 
void count(long long v) {
    long long prev = v;
    long long centroid = centroidDecomp[v];
    if (centroid != -1 && blackArray[centroid].count(prev) == 0) {
        blackArray[centroid][prev] = 0;
        for (auto to: centroidArrays[prev]) {
            blackArray[centroid][prev] += d[centroid][to];
        }
    }
 
}
 
void update(long long v) {
    if (!color[v]) {
        long long prev = v;
        sizeBlack[v]--;
        sizeWhite[v]++;
        long long centroid = centroidDecomp[v];
        while (centroid != -1) {
            sizeBlack[centroid]--;
            sizeWhite[centroid]++;
            blackArray[centroid][prev] -= d[centroid][v];
            black[centroid] -= d[centroid][v];
            white[centroid] += d[centroid][v];
            whiteArray[centroid][prev] += d[centroid][v];
            prev = centroid;
            centroid = centroidDecomp[centroid];
        }
    } else {
        long long prev = v;
        sizeBlack[v]++;
        sizeWhite[v]--;
        long long centroid = centroidDecomp[v];
        while (centroid != -1) {
            sizeBlack[centroid]++;
            sizeWhite[centroid]--;
            blackArray[centroid][prev] += d[centroid][v];
            black[centroid] += d[centroid][v];
            white[centroid] -= d[centroid][v];
            whiteArray[centroid][prev] -= d[centroid][v];
            prev = centroid;
            centroid = centroidDecomp[centroid];
        }
    }
    color[v] = !color[v];
}
 
long long get(long long v) {
    long long ans = 0;
    if (!color[v]) {
        long long prev = v;
        long long centroid = centroidDecomp[v];
        ans = black[prev];
        while (centroid != -1) {
            ans -= blackArray[centroid][prev];
            ans += black[centroid];
            ans += d[centroid][v] * (sizeBlack[centroid] - sizeBlack[prev]);
            prev = centroid;
            centroid = centroidDecomp[centroid];
        }
    } else {
        long long prev = v;
        long long centroid = centroidDecomp[v];
        ans = white[prev];
        while (centroid != -1) {
            ans -= whiteArray[centroid][prev];
            ans += white[centroid];
            ans += d[centroid][v] * (sizeWhite[centroid] - sizeWhite[prev]);
            prev = centroid;
            centroid = centroidDecomp[centroid];
        }
    }
    return ans;
}
 
void solve() {
    dfs(0, n, 0, -1);
    for (long long i = 0; i < n; ++i)
        count(i);
}
 
void output() {
    long long x, v;
    for (long long i = 0; i < m; ++i) {
        in >> x >> v;
        --v;
        if (x == 1) {
            update(v);
        } else {
            out << get(v) << "\n";
        }
    }
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}