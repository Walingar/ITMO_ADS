// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
long long n, m, s, f;
const unsigned long long MAX_N = 2017;
using namespace std;
ifstream in("path.in");
ofstream out("path.out");
long long ans = 0;

struct edge {
    long long from, to, w;

    edge(long long x, long long y, long long z) {
        from = x;
        to = y;
        w = z;
    }
};

vector<edge> edges;
vector<vector<long long>> edgesDFS(MAX_N);

void input() {
    in >> n >> m >> s;
    --s;
    for (long long i = 0; i < m; ++i) {
        long long from, to, w;
        in >> from >> to >> w;
        --from;
        --to;
        edges.push_back(edge(from, to, w));
        edgesDFS[from].push_back(to);
    }
}

long long INF = LLONG_MAX / 2;

vector<long long> d(MAX_N, INF);
vector<long long> ok(MAX_N, true);
vector<bool> was(MAX_N);

void reset() {
    for (long long i = 0; i < n; ++i) {
        was[i] = false;
    }
}

void dfs(long long v) {
    was[v] = true;
    ok[v] = false;
    for (auto to: edgesDFS[v]) {
        if (!was[to])
            dfs(to);
    }
}



void solve() {
    d[s] = 0;
    long long x;
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < m; ++j)
            if (d[edges[j].from] < INF) {
                if (d[edges[j].to] > d[edges[j].from] + edges[j].w) {
                    d[edges[j].to] = max(-INF, d[edges[j].from] + edges[j].w);
                    if (i == n - 1) {
                        reset();
                        dfs(edges[j].to);
                    }
                }
            }
    }
}

void output() {
    for (long long i = 0; i < n; ++i) {
        if (d[i] == INF) out << "*" << "\n";
        else if (!ok[i]) out << "-" << "\n";
        else out << d[i] << "\n";
    }
}

int main() {
    input();
    solve();
    output();
    return 0;
}