#include <bits/stdc++.h>

using namespace std;
const string file_name = "assignment";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");

const long long MAX_N = 1000000000000000000 + 5;
long long n;

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

bool prime(long long val, long long mod) {
    if (val == 2 || n == 3) {
        return true;
    }

    if (val == 1 || val % 2 == 0) {
        return false;
    }

    long long p = 0, q = val - 1;

    while (q % 2 == 0) {
        ++p;
        q /= 2;
    }

    for (int i = 0; i < 9; i++) {
        long long a = (rand() % (val - 2)) + 2;
        long long x = pow(a, q, val);

        if (x == 1 || x == val - 1)
            continue;

        for (int j = 1; j < p; ++j) {
            x = mul(x, x, val);
            if (x == 1)
                return false;
            if (x == val - 1)
                break;
        }

        if (x != val - 1)
            return false;
    }

    return true;
}


void input() {
    srand(NULL);
    inp >> n;
    long long val;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &val);
        if (prime(val, 2)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}


int main() {
    input();
    return 0;
}