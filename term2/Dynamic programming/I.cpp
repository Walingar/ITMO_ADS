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
#include <algorithm>
 
using namespace std;
 
struct task {
    int s, p, t, n;
 
    task(int x, int y, int z, int l) {
        s = x;
        p = y;
        t = z;
        n = l;
    }
};
 
string s;
string p;
vector<vector<long long>> dp;
vector<bool> was;
vector<task> tasks;
int n, T, R0;
 
ifstream in("practice.in");
ofstream out("practice.out");
 
 
void input() {
    in >> n >> T >> R0;
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        in >> x >> y >> z;
        task temp(x, y, z, i + 1);
        tasks.push_back(temp);
    }
    sort(tasks.begin(), tasks.end(), [](task &a, task &b) { return a.s < b.s; });
    dp.assign(n + 2, vector<long long>(T + 2, R0));
    for (int i = 0; i <= T; ++i) {
        dp[0][i] = R0;
    }
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = R0;
    }
 
}
 
 
void solve() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= T; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= tasks[i - 1].t &&
                (dp[i - 1][j - tasks[i - 1].t] + tasks[i - 1].p > dp[i][j]) &&
                dp[i - 1][j - tasks[i - 1].t] >= tasks[i - 1].s)
 
                dp[i][j] = dp[i - 1][j - tasks[i - 1].t] + tasks[i - 1].p;
        }
}
 
void output() {
    int i = n;
    int j = T;
    std::vector<int> ans;
    while (dp[i][j] != R0) {
        if (dp[i - 1][j] == dp[i][j]) {
            --i;
        } else {
            j -= tasks[i - 1].t;
            ans.push_back(tasks[i - 1].n);
            --i;
        }
    }
    out << dp[n][T] << '\n';
    for (int i = ans.size() - 1; i > -1; --i) {
        out << ans[i] << " ";
    }
}
 
int main() {
    input();
    solve();
    output();
    in.close();
    out.close();
}