#include <bits/stdc++.h>

using namespace std;
const string file_name = "mincost";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");

const int MAX_N = 1000000 + 5;
int n;

vector<int> prime(static_cast<unsigned long>(MAX_N + 1), true);

void input() {
    n = MAX_N;
    for (int i = 0; i <= n; ++i) {
        prime[i] = i;
    }
    for (int i = 2; i <= n; ++i)
        if (prime[i] == i) {
            long long sqr = i * 1ll * i;
            for (long long j = sqr; j <= n; j += i)
                prime[j] = i;
        }

    inp >> n;
    int val;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &val);
        ans.clear();
        while (val != 1) {
            ans.push_back(prime[val]);
            val /= prime[val];
        }
        sort(ans.begin(), ans.end());
        for (auto j: ans) {
            printf("%d ", j);
        }
        printf("\n");
    }
}


int main() {
    input();
    return 0;
}