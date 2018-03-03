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
 
vector<string> strings;
string t, s;
int n, m, f;
string ans_s = "";
const long long p = 37;
const unsigned int MAX_N = 10000 + 50;
vector<long long> pm(MAX_N);
//#define in cin
//#define out cout
ifstream in("substr3.in");
ofstream out("substr3.out");
 
void input() {
    in >> n;
    s = "";
    for (int i = 0; i < n; ++i) {
        in >> s;
        strings.push_back(s);
    }
}
 
long long get_hash(string &st, int l, int len) {
    long long ans = 0;
 
    for (int i = l; i < l + len; ++i)
        ans += (st[i] - 'a' + 1) * pm[i - l];
 
    return ans;
}
 
set<long long> &get_hashes(string &st, int len) {
    auto *ans = new set<long long>;
    for (int i = 0; i <= (int) st.length() - len; ++i)
        (*ans).insert(get_hash(st, i, len));
    return *ans;
}
 
void GCS() {
    int l = 0, r = MAX_N;
    for (int i = 0; i < n; ++i)
        if (r > strings[i].length())
            r = (int) strings[i].length();
    ++r;
    long long ans = 0;
    while (r - l > 1) {
        int m = (l + r) / 2;
        set<long long> hashes1 = get_hashes(strings[0], m);
        for (int i = 1; i < n; ++i) {
            set<long long> hashes2 = get_hashes(strings[i], m);
            vector<long long> temp;
            for (auto &hash: hashes1)
                if (hashes2.count(hash) == 0)
                    temp.push_back(hash);
            for (auto &hash: temp)
                hashes1.erase(hash);
        }
        if (hashes1.size() == 0) {
            r = m;
        } else {
            l = m;
            ans = *hashes1.begin();
        }
    }
    if (l == 0) {
        ans_s = "";
        return;
    }
    for (int i = 0; i <= strings[0].length() - l; ++i) {
        long long hash = get_hash(strings[0], i, l);
        if (hash == ans) {
            ans_s = strings[0].substr(i, l);
            return;
        }
    }
 
}
 
void pre_calc() {
    pm[0] = 1;
    for (int i = 1; i < MAX_N; ++i)
        pm[i] = pm[i - 1] * p;
}
 
void solve() {
    pre_calc();
}
 
void output() {
    GCS();
    out << ans_s;
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}