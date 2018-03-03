//
// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
int n, m;
 
int main() {
    std::ifstream in("knapsack.in");
    std::ofstream out("knapsack.out");
    in >> n;
    in >> m;
    int c[n];
    int w[n];
    int dp[n + 1][m + 1];
    for (int i = 0; i < n; ++i) {
        in >> w[i];
    }
    for (int i = 0; i < n; ++i) {
        in >> c[i];
    }
    for (int i = 0; i <= m; ++i) {
        dp[0][i] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1] && (dp[i - 1][j - w[i - 1]] + c[i - 1] > dp[i][j])) {
                dp[i][j] = dp[i - 1][j - w[i - 1]] + c[i - 1];
            }
        }
    }
    //int ans = 0;
    /*for (int i = 0; i <= m; ++i) {
        if (ans < dp[n][i]) {
            ans = dp[n][i];
        }
    }*/
    /*for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            out << dp[i][j] << " ";
        }
        out <<'\n';
    }*/
    int i = n;
    int j = m;
    std::vector <int> ans;
    while (dp[i][j] != 0) {
        if (dp[i - 1][j] == dp[i][j]) {
            --i;
        } else {
            j -= w[i - 1];
            ans.push_back(i--);
        }
    }
    out << ans.size() << '\n';
    for(int i =  ans.size() - 1; i > -1; --i) {
        out << ans[i] << " ";
    }
    in.close();
    out.close();
    return 0;
}