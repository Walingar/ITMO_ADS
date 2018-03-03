#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string fileName = "cycle";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, m;
unsigned int MAX_N = 100 * 1000;
vector<vector<int>> edges(MAX_N);
vector<int> color(MAX_N, 0);
vector<bool> was(MAX_N, false);
vector<int> ans;
vector<int> path(MAX_N, -1);
int start, finish;

void input() {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        edges[x - 1].push_back(y - 1);
    }
}

void output() {
    out << "YES" << "\n";
    vector<int> cycle;
    for (int v = finish; v != start; v = path[v])
        cycle.push_back(v + 1);
    cycle.push_back(start + 1);
    reverse(cycle.begin(), cycle.end());
    for(auto i:cycle) out << i << " ";
}

void dfs(int v) {
    was[v] = true;
    for (auto to: edges[v]) {
        if (!was[to])
            dfs(to);
    }
    ans.push_back(v);
}

void solve() {
    for (int i = 0; i < n; ++i)
        if (!was[i])
            dfs(i);
    output();
}


bool cdfs(int v) {
    color[v] = 1;
    bool b = true;
    for (auto i: edges[v]) {
        if (color[i] == 0) {
            path[i] = v;
            if (!cdfs(i)) return false;
        } else if (color[i] == 1) {
            start = i;
            finish = v;
            return false;
        }
    }
    color[v] = 2;
    return true;
}

bool check() {
    for (int i = 0; i < n; ++i)
        if (color[i] == 0)
            if (!cdfs(i)) return false;
    return true;
}

int main() {
    input();
    if (!check()) output();
    else out << "NO";
    return 0;
}