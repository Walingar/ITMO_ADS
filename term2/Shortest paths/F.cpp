// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

long long n, m, s, f;
const unsigned long long MAX_N = 260;
using namespace std;
ifstream in("negcycle.in");
ofstream out("negcycle.out");
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

void input() {
    in >> n;
    m = 0;
    for (long long i = 0; i < n; ++i)
        for (long long j = 0; j < n; ++j) {
            long long temp;
            in >> temp;
            if (temp != 1000 * 1000 * 1000) {
                edges.push_back(edge(i, j, temp));
                ++m;
            }
        }

}

long long INF = LLONG_MAX / 2;

vector<long long> d(MAX_N, 0);
vector<long long> path(MAX_N, -1);
vector<long long> p;
void solve() {
    long long was = -1;
    for (long long i = 0; i < n; ++i) {
        was = -1;
        for (long long j = 0; j < m; ++j)
            if (d[edges[j].to] > d[edges[j].from] + edges[j].w) {
                d[edges[j].to] = max(-INF, d[edges[j].from] + edges[j].w);
                path[edges[j].to] = edges[j].from;
                was = edges[j].to;
            }
    }

    if (was == -1) {
        out << "NO";
        exit(0);
    } else {
        long long y = was;
        for (long long i = 0; i < n; ++i)
            y = path[y];
        for (long long cur = y;; cur = path[cur]) {
            p.push_back(cur);
            if (cur == y && p.size() > 1) break;
        }
    }

}

void output() {
    reverse(p.begin(), p.end());
    out << "YES" << "\n";
    out << p.size() << "\n";
    for (auto i : p) out << i + 1 << ' ';
}

int main() {
    input();
    solve();
    output();
    return 0;
}