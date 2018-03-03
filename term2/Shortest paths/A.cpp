// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
 
int n, m;
const unsigned int MAX_N = 300000;
using namespace std;
ifstream in("pathbge1.in");
ofstream out("pathbge1.out");
int ans = 0;
 
vector<vector<int> > edges(MAX_N + 2);
 
void input() {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int from, to;
        in >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
}
vector<int> d(MAX_N, 0);
void solve() {
    int s = 1;
    queue<int> q;
    q.push(s);
    vector<bool> was(MAX_N, false);
    was[s] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for(auto to: edges[v]) {
            if (!was[to]) {
                was[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
}
 
void output() {
    for (int i = 1; i <= n; ++i) out << d[i] << " ";
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}