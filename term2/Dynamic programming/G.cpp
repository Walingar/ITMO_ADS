//
// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>
 
int n, l;
long long h[2001];
long long w[2001];
long long dp[2001];
std::string s;
std::ifstream in("bookshelf.in");
std::ofstream out("bookshelf.out");
std::string ans = "";
 
int main() {
    in >> n >> l;
    for (int i = 0; i < n; ++i) {
        in >> h[i] >> w[i];
    }
    dp[0] = h[0];
    for (int i = 1; i < n; ++i) {
        dp[i] = dp[i - 1] + h[i];
        long long hm = -1;
        long long len = 0;
        for (int j = i; len < l && j > -1; --j) {
            hm = std::max(h[j], hm);
            len += w[j];
            if (len > l) break;
            dp[i] = std::min(dp[i], dp[j - 1] + hm);
        }
    }
    out << dp[n - 1];
    in.close();
    out.close();
    return 0;
}