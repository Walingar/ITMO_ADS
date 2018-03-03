#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <math.h>
 
using namespace std;
 
string p, t, s;
int n, m, f;
const unsigned int MAX_N = 2000000 + 50;
vector<int> pi(MAX_N, 0);
#define in cin
#define out cout
//ifstream in("path.in");
//ofstream out("path.out");
 
void get_prefix_function() {
    int j = 0;
    for (int i = 1; i < s.length(); ++i) {
        j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            pi[i] = ++j;
    }
}
 
 
void input() {
    in >> s;
}
 
 
void solve() {
    get_prefix_function();
}
 
 
void output() {
    int k = pi[s.length() - 1];
    if (k == 0) {
        out << s.length();
        return;
    }
    if (s.length() % (s.length() - k) == 0) {
        out << s.length() - k;
        return;
    }
    out << s.length();
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}