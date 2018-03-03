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
const unsigned long long MAX_N = 2017;
using namespace std;
ifstream in("pathmgep.in");
ofstream out("pathmgep.out");
long long ans = 0;
 
vector<vector<pair<long long, long long>>> edges(MAX_N);
 
 
void input() {
    in >> n >> s >> f;
    --s;
    --f;
    m = 0;
    for (long long i = 0; i < n; ++i)
        for (long long j = 0; j < n; ++j) {
            long long temp;
            in >> temp;
            if (temp != 0 && temp != -1) {
                edges[i].push_back({j, temp});
            }
        }
}
 
vector<long long> d(MAX_N, LLONG_MAX);
 
void solve() {
    d[s] = 0;
    vector<bool> was(MAX_N, false);
    for (long long i = 0; i < n; ++i) {
        long long v = -1;
        for (long long j = 0; j < n; ++j)
            if (!was[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == LLONG_MAX)
            break;
        was[v] = true;
        for (auto to: edges[v])
            if (d[v] + to.second < d[to.first])
                d[to.first] = d[v] + to.second;
    }
}
 
void output() {
    if (d[f] == LLONG_MAX) d[f] = -1;
    out << d[f];
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}