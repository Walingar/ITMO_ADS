// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <climits>

long long n, m, s, f;
const unsigned long long MAX_N = 205;
using namespace std;
ifstream in("pathsg.in");
ofstream out("pathsg.out");
long long ans = 0;

vector<vector<long long>> d(MAX_N, vector<long long>(MAX_N, LLONG_MAX));


void input() {
    in >> n >> m;
    for (long long i = 0; i < m; ++i) {
        long long from, to, w;
        in >> from >> to >> w;
        --from;
        --to;
        d[from][to] = w;
    }
}

void solve() {
    for (long long k = 0; k < n; ++k)
        d[k][k] = 0;

    for (long long k = 0; k < n; ++k)
        for (long long i = 0; i < n; ++i)
            for (long long j = 0; j < n; ++j)
                if (d[i][k] < LLONG_MAX && d[k][j] < LLONG_MAX)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void output() {
    for (long long k = 0; k < n; ++k) {
        for (long long i = 0; i < n; ++i) {
            if (d[k][i] != LLONG_MAX) out << d[k][i] << " ";
            else out << "-1" << " ";
        }

        out << "\n";
    }
}

int main() {
    input();
    solve();
    output();
    return 0;
}