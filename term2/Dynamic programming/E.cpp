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
long long dp[501][501];
int a[501];
int p[501][501];
std::ifstream in("matrix.in");
std::ofstream out("matrix.out");
struct matrix {
    int a;
    int b;
};
std::string ans;
 
long long counting(int l, int r) {
    if (dp[l][r] == -1) {
        if (l == r - 1) {
            return 0;
        } else {
            dp[l][r] = LONG_LONG_MAX;
            int min = 501;
            for (int i = l + 1; i < r; ++i) {
                if (dp[l][r] > counting(l, i) + counting(i, r) + a[l] * a[i] * a[r]) {
                    dp[l][r] = counting(l, i) + counting(i, r) + a[l] * a[i] * a[r];
                    p[l][r] = i;
                }
            }
        }
    }
    return dp[l][r];
}
 
std::string getAns(int l, int r) {
    if (l == r - 1) {
        return "A";
    } else {
        return ("(" + getAns(l, p[l][r]) + getAns(p[l][r], r) + ")");
    }
}
 
int main() {
    in >> n;
    matrix arr[n];
    for (int i = 0; i < n; ++i) {
        in >> arr[i].a >> arr[i].b;
    }
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            dp[i][j] = -1;
        }
        dp[i][i] = 0;
    }
    a[0] = arr[0].a;
    //out << a[0] << " ";
    for (int i = 0; i < n + 1; ++i) {
        a[i + 1] = arr[i].b;
        //out << a[i] << " ";
    }
 
    int psdfgsdsf = counting(0, n);
    out << getAns(0, n);
    in.close();
    out.close();
    return 0;
}