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
 
string t, s;
int n, m, f;
const int END = 256;
const unsigned int MAX_N = 400000 + 50;
vector<int> suff(MAX_N);
vector<int> lcp(MAX_N);
//#define in cin
//#define out cout
ifstream in("count.in");
ofstream out("count.out");
 
int get_letter_ind(char ch) {
    return ch - '#';
}
 
vector<int> classes(MAX_N);
vector<int> classes_temp(MAX_N);
vector<int> suff_temp(MAX_N);
 
void build_suff_array() {
    vector<int> cnt(END, 0);
    for (int i = 0; i < n; ++i)
        ++cnt[get_letter_ind(s[i])];
    for (int i = 0; i + 1 < END; ++i)
        cnt[i + 1] += cnt[i];
 
    for (int i = 0; i < n; ++i)
        suff[--cnt[get_letter_ind(s[i])]] = i;
    int count = 1;
    classes[suff[0]] = 0;
 
    for (int i = 1; i < n; ++i) {
        if (s[suff[i]] != s[suff[i - 1]])
            ++count;
        classes[suff[i]] = count - 1;
    }
 
    for (int l = 0; (1 << l) < n; ++l) {
        int x = 1 << l;
        for (int i = 0; i < n; ++i) {
            suff_temp[i] = suff[i] - x;
            if (suff_temp[i] < 0)
                suff_temp[i] += n;
        }
 
        vector<int> cnt(count, 0);
        for (int i = 0; i < n; ++i)
            ++cnt[classes[suff_temp[i]]];
        for (int i = 0; i + 1 < count; ++i)
            cnt[i + 1] += cnt[i];
        for (int i = n - 1; i > -1; --i)
            suff[--cnt[classes[suff_temp[i]]]] = suff_temp[i];
 
        count = 1;
        classes[suff[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (classes[suff[i]] != classes[suff[i - 1]] ||
                classes[(suff[i] + x) % n] != classes[(suff[i - 1] + x) % n])
                ++count;
            classes_temp[suff[i]] = count - 1;
        }
        classes = classes_temp;
    }
}
 
vector<int> pos(MAX_N);
 
void build_lcp() {
    for (int i = 0; i < n; ++i)
        pos[suff[i]] = i;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (k > 0)
            --k;
        if (pos[i] == n - 1) {
            lcp[n - 1] = -1;
            k = 0;
        } else {
            int cur = suff[pos[i] + 1];
            while (max(i + k, cur + k) < n && s[i + k] == s[cur + k])
                ++k;
            lcp[pos[i]] = k;
        }
    }
}
 
void input() {
    in >> s;
    s += '#';
    n = (int) s.length();
}
 
void solve() {
    build_suff_array();
    build_lcp();
}
 
void output() {
    long long ans = 0;
    for (int i = 1; i < n - 1; ++i)
        ans += n - suff[i] - 1 - lcp[i];
    out << ans + n - 1 - suff[n - 1];
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}