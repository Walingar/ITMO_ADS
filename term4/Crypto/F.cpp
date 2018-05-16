#include <bits/stdc++.h>

using namespace std;
const string file_name = "mincost";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");
long long n, m, c, e;

long long gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1 = 0, y1 = 0;
    long long d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

long long EuclidAdv(long long a, long long m) {
    long long x, y;
    long long ans = gcd(a, m, x, y);
    return (x + m) % m;
}

int kto(int *a, int *p, int size) {
    int r[size][size];
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            r[i][j] = EuclidAdv(p[i], p[j]);

    int result = 0;
    int mult_p = 1;
    int x[size] = {0};
    for (int i = 0; i < 2; ++i) {
        x[i] = a[i];
        for (int j = 0; j < i; ++j) {
            x[i] = (x[i] - x[j]) * r[j][i];
            x[i] = x[i] % p[i];
            if (x[i] < 0) {
                x[i] += p[i];
            }
        }
        result += mult_p * x[i];
        mult_p *= p[i];
    }
    return result;
}

vector<long long> factorization(long long n) {
    vector<long long> ans;
    for (long long i = 2; i <= n; ++i) {
        if (n % i == 0) {
            ans.push_back(i);
            ans.push_back(n / i);
            break;
        }
    }
    return ans;
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long mul(long long a, long long n, long long m) {
    long long r = 0;
    while (n > 0) {
        if (n % 2 == 1)
            r = (r + a) % m;
        a = (a + a) % m;
        n /= 2;
    }
    return r;
}

long long pow(long long a, long long n, long long m) {
    long long res = 1;
    while (n > 0) {
        if ((n & 1) > 0)
            res = mul(res, a, m);
        a = mul(a, a, m);
        n >>= 1;
    }
    return res;
}

void input() {
    inp >> n >> e >> c;
    auto factor = factorization(n);
    long long phi = (factor[0] - 1) * (factor[1] - 1);
    // e*d = 1 mod phi -> e*d +
    long long d = EuclidAdv(e, phi);
    printf("%lld", pow(c, d, n));
}


int main() {
    input();
    return 0;
}