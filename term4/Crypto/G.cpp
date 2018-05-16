#include <bits/stdc++.h>

using namespace std;
const string file_name = "assignment";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");

#define PI 3.14159265359
vector<int> n;
vector<int> m;
vector<int> res;
bool neg_n = false, neg_m = false;
bool neg = true;

void input() {
    string n_s, m_s;
    inp >> n_s >> m_s;
    if (n_s[0] == '-') {
        neg_n = true;
        n_s[0] = '0';
    }
    if (m_s[0] == '-') {
        neg_m = true;
        m_s[0] = '0';
    }
    if (neg_m && neg_n || !neg_m && !neg_n) {
        neg = false;
    }
    for (auto c: n_s) {
        n.push_back((int) (c - '0'));
    }
    for (auto c: m_s) {
        m.push_back((int) (c - '0'));
    }
    reverse(n.begin(), n.end());
    reverse(m.begin(), m.end());
}

void fft(vector<complex<double>> &a) {
    auto n = (int) a.size();
    if (n == 1) {
        return;
    }

    vector<complex<double>> a0(static_cast<unsigned long>(n / 2));
    vector<complex<double>> a1(static_cast<unsigned long>(n / 2));

    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    fft(a0);
    fft(a1);

    double ang = 2 * PI / n;
    complex<double> w(1, 0);
    complex<double> wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }
}

void fft_back(vector<complex<double>> &a) {
    auto n = (int) a.size();
    if (n == 1) {
        return;
    }

    vector<complex<double>> a0(static_cast<unsigned long>(n / 2));
    vector<complex<double>> a1(static_cast<unsigned long>(n / 2));

    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    fft_back(a0);
    fft_back(a1);

    double ang = -2 * PI / n;
    complex<double> w(1, 0);
    complex<double> wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        a[i] /= 2;
        a[i + n / 2] /= 2;
        w *= wn;
    }
}

void solve() {
    vector<complex<double>> fn(n.begin(), n.end());
    vector<complex<double>> fm(m.begin(), m.end());
    size_t size = 1;
    while (size < max(n.size(), m.size())) {
        size *= 2;
    }
    size *= 2;

    fn.resize(size);
    fm.resize(size);

    fft(fn);
    fft(fm);
    for (size_t i = 0; i < size; ++i)
        fn[i] *= fm[i];
    fft_back(fn);

    res.resize(size);
    for (size_t i = 0; i < size; ++i)
        res[i] = int(fn[i].real() + 0.5);

    int carry = 0;
    for (size_t i = 0; i < size; ++i) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }
}

void output() {
    int i = static_cast<int>(res.size() - 1);
    while (i >= 0 && res[i] == 0) {
        --i;
    }
    if (i == -1) {
        printf("%d", 0);
        exit(0);
    }
    if (neg) {
        printf("-");
    }
    for (; i >= 0; --i) {
        printf("%d", res[i]);
    }
}


int main() {
    input();
    solve();
    output();
    return 0;
}