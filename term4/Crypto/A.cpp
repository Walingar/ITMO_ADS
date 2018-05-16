#include <bits/stdc++.h>

using namespace std;
const string file_name = "mincost";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");

const int MAX_N = 1000000 + 5;
int n;

vector<char> prime(static_cast<unsigned long>(MAX_N + 1), true);

void input() {

    n = MAX_N;
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i <= n; ++i)
        if (prime[i]) {
            long long sqr = i * 1ll * i;
            for (long long j = sqr; j <= n; j += i)
                prime[j] = false;
        }

    inp >> n;
    int val;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &val);
        if (prime[val]) {
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