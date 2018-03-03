//
// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
int n, m;
int dp[5001][5001];
int main() {
    std::ifstream in("levenshtein.in");
    std::ofstream out("levenshtein.out");
    std::string a, b;
    in >> a >> b;
    n = a.length();
    m = b.length();
    for (int i = 0; i <= n; ++i){
        dp[i][0] = i;
    }
    for (int i = 0; i <= m; ++i){
        dp[0][i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1);
                dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + 1);
            }
        }
    }
    out << dp[n][m];
    in.close();
    out.close();
    return 0;
}