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
 
using namespace std;
 
string s;
int n, m, f;
const unsigned int MAX_N = 1000000 + 50;
vector<int> pi(MAX_N, 0);
#define in cin
#define out cout
//ifstream in("path.in");
//ofstream out("path.out");
 
void get_preffix_function() {
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
    get_preffix_function();
 
}
 
 
void output() {
    for (int i = 0; i < s.length(); ++i)
        out << pi[i] << " ";
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}