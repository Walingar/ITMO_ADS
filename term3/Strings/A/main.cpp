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
const unsigned int MAX_N = 100000 + 50;
const long long p_1 = 4;
const long long p_2 = 9;
vector<long long> pref_hash_1(MAX_N, 0);
vector<long long> pref_hash_2(MAX_N, 0);
vector<long long> pows_1(MAX_N, 1);
vector<long long> pows_2(MAX_N, 1);
 
#define in cin
#define out cout
//ifstream in("path.in");
//ofstream out("path.out");
 
 
void input() {
    in >> s;
    in >> m;
    n = (int) s.length();
}
 
void pows() {
    for (int i = 1; i < n; ++i) {
        pows_1[i] = pows_1[i - 1] * p_1;
        pows_2[i] = pows_2[i - 1] * p_2;
    }
}
 
void get_hash_s() {
    for (int i = 0; i < s.length(); ++i) {
        if (i != 0) {
            pref_hash_1[i] += pref_hash_1[i - 1];
            pref_hash_2[i] += pref_hash_2[i - 1];
        }
        pref_hash_1[i] += (s[i] - 'a' + 1) * pows_1[i];
        pref_hash_2[i] += (s[i] - 'a' + 1) * pows_2[i];
    }
}
 
 
void solve() {
    pows();
    get_hash_s();
 
}
 
long long hash_1, hash_2;
 
bool isSimilar(int a, int b, int c, int d) {
    if (a > c) {
        swap(a, c);
        swap(b, d);
    }
    if (b - a != d - c)
        return false;
    long long len = b - a + 1;
 
    hash_1 = pref_hash_1[a + len - 1];
    if (a) hash_1 -= pref_hash_1[a - 1];
    hash_2 = pref_hash_1[c + len - 1];
    if (c) hash_2 -= pref_hash_1[c - 1];
 
    bool ans_1 = hash_1 * pows_1[c - a] == hash_2;
 
 
    hash_1 = pref_hash_2[a + len - 1];
    if (a) hash_1 -= pref_hash_2[a - 1];
    hash_2 = pref_hash_2[c + len - 1];
    if (c) hash_2 -= pref_hash_2[c - 1];
 
    bool ans_2 = hash_1 * pows_2[c - a] == hash_2;
 
    return ans_1 && ans_2;
}
 
 
void output() {
    int a, b, c, d;
    for (int i = 0; i < m; ++i) {
        in >> a >> b >> c >> d;
        --a, --b, --c, --d;
        out << (isSimilar(a, b, c, d) ? "Yes" : "No") << "\n";
    }
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}