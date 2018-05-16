#include <bits/stdc++.h>

using namespace std;
const string file_name = "mincost";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");

const int SQRT_MAX_N = 100000;
const int S = 50000;
bool first_primes[SQRT_MAX_N], block[S];
int block_primes[SQRT_MAX_N];

int mul(int a, int n) {
    int r = 0;
    while (n > 0) {
        if (n % 2 == 1)
            r = r + a;
        a = a + a;
        n /= 2;
    }
    return r;
}

void input() {
    int n, x, h = 0, count = 0;
    scanf("%d", &n);
    scanf("%d", &x);

    auto n_sqrt = (int) sqrt(n);
    for (int i = 2; i <= n_sqrt; ++i)
        if (!first_primes[i]) {
            block_primes[count++] = i;
            long long sqr = i * 1ll * i;
            if (sqr <= n_sqrt)
                for (long long j = sqr; j <= n_sqrt; j += i)
                    first_primes[j] = true;
        }
    int max_k = n / S;
    for (int k = 0; k <= max_k; ++k) {
        memset(block, 0, sizeof(block));
        int start = k * S;
        for (int i = 0; i < count; ++i) {
            int start_idx = (start + block_primes[i] - 1) / block_primes[i];
            if (start_idx < 2) {
                start_idx = 2;
            }
            for (int j = start_idx * block_primes[i] - start; j < S; j += block_primes[i])
                block[j] = true;
        }
        if (k == 0)
            block[0] = block[1] = true;
        for (int i = 0; i < S && start + i <= n; ++i)
            if (!block[i])
                h = mul(h, x) + i + k * S;
    }

    printf("%d", h);
}


int main() {
    input();
    return 0;
}