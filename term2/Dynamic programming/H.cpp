//
// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>
 
long long  n, m;
long long dp[1 << 19][19];
std::string s;
std::ifstream in("salesman.in");
std::ofstream out("salesman.out");
long long ans = 3.5e9;
 
struct Line {
    long long  to;
    long long w;
 
    Line(long long  TO, long long W) {
        to = TO;
        w = W;
    }
};
 
int  main() {
    in >> n >> m;
    std::vector<Line> Lines[19];
    for (long long  i = 0; i < m; ++i) {
        long long  from, to;
        long long w;
        in >> from >> to >> w;
        Lines[--from].push_back(Line(--to, w));
        Lines[to].push_back(Line(from, w));
    }
    for (long long  i = 0; i < 1 << n; ++i) {
        for (long long  v = 0; v < n; ++v) {
            dp[i][v] = 3.5e9;
        }
    }
    for (long long  i = 0; i < n; ++i) {
        dp[1 << i][i] = 0;
    }
    //dp[0][0] = 0;
    for (long long  i = 0; i < 1 << n; ++i) {
        for (long long  v = 0; v < n; ++v) {
            if (i & (1 << v)) {
                for (long long  k = 0; k < Lines[v].size(); ++k) {
                    long long  nowTo = Lines[v][k].to;
                    long long nowW = Lines[v][k].w;
                    if (!(i & (1 << nowTo))) {
                        if (dp[i + (1 << nowTo)][nowTo] > dp[i][v] + nowW) {
                            dp[i + (1 << nowTo)][nowTo] = dp[i][v] + nowW;
                        }
                    }
                }
            }
        }
    }
    for (long long  i = 0; i < n; ++i) {
        if (ans > dp[(1 << n) - 1][i]) {
            ans = dp[(1 << n) - 1][i];
        }
    }
    if (ans == 3.5e9) ans = -1;
    out << ans;
    return 0;
}