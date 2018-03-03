#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string fileName = "cond";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, m;
unsigned int MAX_N = 20000;
vector<vector<int>> edges(MAX_N);
vector<vector<int>> edgesBack(MAX_N);
vector<int> color(MAX_N, 0);
vector<bool> was(MAX_N, false);
vector<int> component;
vector<int> components(MAX_N, 0);
vector<int> order;
int ans = 0;
int ans2 = 0;
vector<int> path(MAX_N, -1);
int start, finish;

void input() {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        edges[x - 1].push_back(y - 1);
        edgesBack[y - 1].push_back(x - 1);
    }
}

void output() {
    out << ans << " ";
    //vector<vector<int>> edges((unsigned int) ans);
    vector<vector<int>> a((unsigned int)ans, vector<int> ((unsigned int)ans,0));
    for (int i = 0; i < n; i++)
        for (auto to: edges[i]) {
            if (a[components[i] - 1][ components[to] - 1] == 0 && components[i] != components[to]) {
                ans2++;
                a[components[i] - 1][ components[to] - 1] = 1;
            }
        }
    out << ans2;
    //for (auto i:components) if (i != 0) out << i << " ";
}

bool cdfs(int v) {
    was[v] = true;
    component.push_back(v);
    for (auto to: edgesBack[v]) {
        if (!was[to])
            cdfs(to);
    }
}

void dfs(int v) {
    was[v] = true;
    for (auto to: edges[v]) {
        if (!was[to])
            dfs(to);
    }
    order.push_back(v);
    //ans.push_back(v);
}

void solve() {
    was.assign(MAX_N, false);
    for (int i = 0; i < n; ++i)
        if (!was[i])
            dfs(i);
    was.assign(MAX_N, false);
    for (int i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!was[v]) {
            ++ans;
            cdfs(v);
            for (auto j: component) components[j] = ans;
            component.clear();
        }
    }
}


bool check() {
    for (int i = 0; i < n; ++i)
        if (color[i] == 0)
            if (!cdfs(i)) return false;
    return true;
}

int main() {
    input();
    solve();
    output();
    return 0;
}