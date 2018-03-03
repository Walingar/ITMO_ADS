//
// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>
 
int n;
int dp[2001][2001];
std::string s;
std::ifstream in("palindrome.in");
std::ofstream out("palindrome.out");
std::string ans = "";
 
int counting(int l, int r) {
    if (dp[l][r] == -1) {
        if (s[l] == s[r]) {
            dp[l][r] = counting(l + 1, r - 1) + 2;
            //ans += s[l];
        } else {
            dp[l][r] = std::max(counting(l + 1, r), counting(l, r - 1));
        }
    }
    return dp[l][r];
}
 
std::string getAns(int l, int r) {
    if (l <= r && dp[l][r] != -1) {
        if (s[l] == s[r]) {
            if (l == r) {
                return s[r] + std::string();
            } else {
                return s[l] + getAns(l + 1, r - 1) + s[l];
            }
        }
        if (dp[l][r] == dp[l + 1][r]) {
            return getAns(l + 1, r);
        } else {
            return getAns(l, r - 1);
        }
    }
    return "";
}
 
int main() {
    in >> s;
    n = s.length();
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            dp[i][j] = -1;
            if (i > j) {
                dp[i][j] = 0;
            }
        }
        dp[i][i] = 1;
    }
    out << counting(0, n - 1) << "\n";
 
    out << getAns(0, n - 1);
    in.close();
    out.close();
    return 0;
}