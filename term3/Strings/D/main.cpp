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
    in >> p;
    in >> t;
}
 
 
void solve() {
    s = p + "#" + t;
    get_prefix_function();
}
 
 
void output() {
    vector<int> ans;
    for (int i = (int) p.length(); i < s.length(); ++i) {
        if (pi[i] == p.length())
            ans.push_back(i - 2 * (int) p.length() + 1);
    }
    out << ans.size() << "\n";
    for (auto i: ans)
        out << i << " ";
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}