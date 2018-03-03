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
#include <stack>
 
using namespace std;
 
 
long long n, m, f;
long long END = 256;
const unsigned long long MAX_N = 150000 + 50;
vector<long long> s(MAX_N);
vector<long long> suff(MAX_N);
vector<long long> lcp(MAX_N);
//#define in cin
//#define out cout
ifstream in("refrain.in");
ofstream out("refrain.out");
 
long long get_letter_ind(long long ch) {
    return ch;
}
 
vector<long long> classes(MAX_N);
vector<long long> classes_temp(MAX_N);
vector<long long> suff_temp(MAX_N);
 
void build_suff_array() {
    vector<long long> cnt(END, 0);
    for (long long i = 0; i < n; ++i)
        ++cnt[get_letter_ind(s[i])];
    for (long long i = 0; i + 1 < END; ++i)
        cnt[i + 1] += cnt[i];
 
    for (long long i = 0; i < n; ++i)
        suff[--cnt[get_letter_ind(s[i])]] = i;
    long long count = 1;
    classes[suff[0]] = 0;
 
    for (long long i = 1; i < n; ++i) {
        if (s[suff[i]] != s[suff[i - 1]])
            ++count;
        classes[suff[i]] = count - 1;
    }
 
    for (long long l = 0; (1 << l) < n; ++l) {
        long long x = 1 << l;
        for (long long i = 0; i < n; ++i) {
            suff_temp[i] = suff[i] - x;
            if (suff_temp[i] < 0)
                suff_temp[i] += n;
        }
 
        vector<long long> cnt(count, 0);
        for (long long i = 0; i < n; ++i)
            ++cnt[classes[suff_temp[i]]];
        for (long long i = 0; i + 1 < count; ++i)
            cnt[i + 1] += cnt[i];
        for (long long i = n - 1; i > -1; --i)
            suff[--cnt[classes[suff_temp[i]]]] = suff_temp[i];
 
        count = 1;
        classes[suff[0]] = 0;
        for (long long i = 1; i < n; ++i) {
            if (classes[suff[i]] != classes[suff[i - 1]] ||
                classes[(suff[i] + x) % n] != classes[(suff[i - 1] + x) % n])
                ++count;
            classes_temp[suff[i]] = count - 1;
        }
        classes = classes_temp;
    }
}
 
vector<long long> pos(MAX_N);
 
void build_lcp() {
    for (long long i = 0; i < n; ++i)
        pos[suff[i]] = i;
    long long k = 0;
    for (long long i = 0; i < n; ++i) {
        if (k > 0)
            --k;
        if (pos[i] == n - 1) {
            lcp[n - 1] = -1;
            k = 0;
        } else {
            long long cur = suff[pos[i] + 1];
            while (max(i + k, cur + k) < n && s[i + k] == s[cur + k])
                ++k;
            lcp[pos[i]] = k;
        }
    }
}
 
void input() {
    in >> n >> m;
    END = m + 10;
    for (long long i = 0; i < n; ++i)
        in >> s[i];
    s[n] = 0;
    ++n;
}
 
struct data {
    long long w;
    long long h;
    long long suf;
};
 
void solve() {
    build_suff_array();
    build_lcp();
    stack<data> stack1;
    long long ans_h = n - 1;
    long long ans_w = 1;
    long long ans_suf = -1;
 
    for (long long i = 1; i < n; ++i) {
        long long cur_w = 1;
        while (!stack1.empty() && lcp[i] <= stack1.top().h) {
            data temp = stack1.top();
            stack1.pop();
            cur_w += temp.w;
            if (cur_w * temp.h > ans_h * ans_w) {
                ans_h = temp.h;
                ans_w = cur_w;
                ans_suf = temp.suf;
            }
        }
 
        if (stack1.empty() || lcp[i] > stack1.top().h) {
            data *temp = new data();
            temp->w = cur_w;
            temp->h = lcp[i];
            temp->suf = i;
            stack1.push(*temp);
        }
    }
    out << ans_h * ans_w << "\n";
    out << ans_h << "\n";
    if (ans_suf != -1)
        for (long long i = 0; i < ans_h; ++i)
            out << s[suff[ans_suf] + i] << " ";
    else
        for (long long i = 0; i < n - 1; ++i)
            out << s[i] << " ";
}
 
void output() {
    /*for (long long i = 1; i < n; ++i) {
        for (long long j = suff[i]; j < n; ++j)
            out << s[j] << " ";
        out << "|" << lcp[i - 1] << "\n";
    }*/
 
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}