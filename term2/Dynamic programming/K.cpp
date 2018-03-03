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
 
const unsigned int MAX_N = 1000000;
const unsigned int MAX_M = 3 * 100000;
string s;
string p;
vector<int> dp(MAX_M, -1);
vector<int> d;
vector<bool> was;
vector<task> tasks;
int n, T, R0, k, m;
int a, b, l, x, y, r;
 
ifstream in("ski.in");
ofstream out("ski.out");
 
 
void input() {
    in >> n >> k >> m;
    for (int i = 0; i < m; ++i) {
        int temp;
        in >> temp;
        d.push_back(temp);
    }
    d.push_back(n + 1);
    sort(d.begin(), d.end());
    dp[0] = 0;
    dp[m] = 0;
}
 
int ans;
 
void solve() {
    for (int i = m - 1; i > -1; --i) {
        l = upper_bound(d.begin(), d.end() - 1, d[i] + k - 1) - d.begin();
        dp[i] = max(dp[i], dp[l] + d[l] - min(d[i] + k - 1, n) - 1);
    }
    ans = (dp[0] += d[0] - 1);
    for (int i = 0; i < m; ++i)
        if (d[i] - k < 0)
            ans = max(ans, dp[i + 1] + d[i + 1] - d[i] - 1);
}
 
void output() {
    out << ans;
}
 
int main() {
    input();
    solve();
    output();
    in.close();
    out.close();
}