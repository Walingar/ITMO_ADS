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
vector<vector<bool>> dp(MAX_N + 2, vector<bool>(MAX_N + 2));
int n, k;
char S;
map<char, string> rules;
ifstream in("automaton.in");
ofstream out("automaton.out");
 
void input() {
    cin >> p;
    cin >> s;
    for (int i = 1; i < s.length() + 1; ++i) dp[i][0] = false;
    for (int i = 1; i < p.length() + 1; ++i) dp[0][i] = false;
    dp[0][0] = true;
}
 
void solve() {
    int j = 1;
    while (p.length() >= j && p[j - 1] == '*') {
        for (int i = 0; i < s.length() + 1; ++i)
            dp[i][j] = true;
        ++j;
    }
    for (int i = 1; i < s.length() + 1; ++i)
        for (int j = 1; j < p.length() + 1; ++j) {
            if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) dp[i][j] = dp[i - 1][j - 1];
            else if (p[j - 1] == '*')
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            else dp[i][j] = false;
        }
}
 
void output() {
    if (dp[s.length()][p.length()])
        cout << "YES";
    else cout << "NO";
}
 
int main() {
    input();
    solve();
    output();
    in.close();
    out.close();
}