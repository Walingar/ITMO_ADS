#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <set>
#include <stack>
#include <limits.h>
#include <fstream>
#include <string>
#include <map>
 
using namespace std;
const unsigned int MAX_N = 10000;
string s;
string p;
vector<int> dp(MAX_N + 2);
int n, k;
char S;
ifstream in("selectw.in");
ofstream out("selectw.out");
vector<int> weights(MAX_N);
vector<vector<int>> tree(MAX_N);
int root = 0;
 
void input() {
    in >> n;
    for (int to = 0; to < n; ++to) {
        int from, w;
        in >> from >> w;
        --from;
        if (from >= 0) tree[from].push_back(to);
        else root = to;
        weights[to] = w;
    }
}
 
vector<bool> was(MAX_N, false);
 
int dfs(int v) {
    int ans = weights[v];
    for (auto to: tree[v])
        for (auto toto: tree[to])
            if (!was[toto]) ans += dfs(toto);
            else ans += dp[toto];
    int temp = 0;
    for (auto to: tree[v])
        if (!was[to]) temp += dfs(to);
        else temp += dp[to];
    dp[v] = max(temp, ans);
    was[v] = true;
    return max(temp, ans);
}
 
void solve() {
    out << dfs(root);
}
 
void output() {
 
}
 
int main() {
    input();
    solve();
    output();
    in.close();
    out.close();
}