#include <bits/stdc++.h>

using namespace std;
const string file_name = "mincost";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");
int a_0, a_1, p_0, p_1;

int EuclidAdv(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
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

void input() {
    inp >> a_0 >> a_1 >> p_0 >> p_1;
    // x == a_0 mod p_0
    // x == a_1 mod p_1
    int p[] = {p_0, p_1};
    int a[] = {a_0, a_1};
    printf("%d", kto(a, p, 2));
}


int main() {
    input();
    return 0;
}