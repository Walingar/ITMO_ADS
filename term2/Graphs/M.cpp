#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string fileName = "game";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, m, s;
unsigned int MAX_N = 100000;
vector<vector<int>> edges(MAX_N);
vector<int> color(MAX_N, 0);
vector<bool> was(MAX_N, false);
vector<int> component;
vector<int> components(MAX_N, 0);
vector<int> order;
int ans = 0;
vector<int> path(MAX_N, -1);
int start, finish;
int ans1 = 0, ans2 = 0;
string as = "Second player wins";
enum token {
    first, second
};
void input() {
    in >> n >> m >> s;
    --s;
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        edges[x - 1].push_back(y - 1);
    }
}

void output() {
    out << as;
}

bool check(int to){
    return edges[to].size() == 0;
}

void dfs(int v, token e) {
    //was[v] = true;
    for (auto to: edges[v]) {
        if (!was[to]) {
            if (e == first && check(to)) as = "First player wins";
            else {
                if (e == first) dfs(to, second);
                else dfs(to, first);
            }
        }
    }
}

void solve() {
    if(!check(s)) dfs(s, first);
    else as = "Second player wins";
}

int main() {
    input();
    solve();
    output();
    return 0;
}