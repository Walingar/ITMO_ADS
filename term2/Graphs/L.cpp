#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string fileName = "hamiltonian";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, m;
unsigned int MAX_N = 100 * 1000;
vector<vector<int>> edges(MAX_N);
vector<int> color(MAX_N, 0);
vector<bool> was(MAX_N, false);
vector<int> ans;

void input() {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        edges[x - 1].push_back(y - 1);
    }
}

bool check() {
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size() - 1; ++i) {
        bool temp = false;
        for (auto j: edges[ans[i]]) {
            if (j == ans[i + 1]) temp = true;
        }
        if (!temp) return false;
    }
    return true;
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
    if (check()) out << "YES";
    else out << "NO";
    //output();
}


bool cdfs(int v) {
    color[v] = 1;
    bool b = true;
    for (auto i: edges[v]) {
        if (color[i] == 0)
            b = cdfs(i);
        if (!b) return b;
        if (color[i] == 1) return false;
    }
    color[v] = 2;
    return b;
}


int main() {
    input();
    solve();
    return 0;
}