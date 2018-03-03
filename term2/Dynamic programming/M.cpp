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
 
const unsigned int MAX_N = 155;
string s;
string p;
vector<vector<int>> dp(MAX_N, vector<int>(MAX_N, 0));
vector<bool> was;
vector<task> tasks;
int n, T, R0;
int a, b, l, x, y;
int leftSide = 0, rightSide = 2 * MAX_N * MAX_N;
ifstream in("bridge.in");
ofstream out("bridge.out");
 
 
void input() {
    in >> x >> a >> y >> b >> l;
}
 
 
void solve() {
    while (leftSide + 1 < rightSide) {
        dp.assign(MAX_N, vector<int>(MAX_N, 0));
        int m = (leftSide + rightSide) / 2;
        int p = 0;
        for (int i = 0; i <= x; i++)
            for (int j = 0; j <= y; j++) {
                for (int k = 0; k <= i; k++) {
                    int t = 0;
                    if (m - k * a + b - 1 > 0) t = m - k * a + b - 1;
                    if (j - t / b >= 0 && dp[i][j] < dp[i - k][j - t / b] + 1) dp[i][j] = dp[i - k][j - t / b] + 1;
                }
                if (p < dp[i][j]) p = dp[i][j];
            }
        if (p >= l)
            leftSide = m;
        else
            rightSide = m;
    }
}
 
void output() {
    out << leftSide;
}
 
int main() {
    input();
    solve();
    output();
    in.close();
    out.close();
}