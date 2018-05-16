#include <bits/stdc++.h>

using namespace std;
const string file_name = "assignment";

//#define inp cin
//#define out cout

ifstream inp(file_name + ".in");
ofstream out(file_name + ".out");

const int MAX_N = 300 + 5;
const int MAX_M = 300 + 5;
int INF = INT_MAX;

int n, m;

vector<vector<int>> table(MAX_N, vector<int>(MAX_N, 0));

void input() {
    inp >> n;
    int value;
    m = n;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            inp >> value;
            table[i][j] = value;
        }
}

pair<int, vector<int>> hungry(vector<vector<int>> &table, int n, int m) {
    vector<int> u(n + 1);
    vector<int> v(m + 1);
    vector<int> matching(m + 1);
    vector<int> way(m + 1);
    vector<int> ans(n + 1);

    for (int row = 1; row <= n; ++row) {
        matching[0] = row;
        int column = 0;

        vector<int> min_v(m + 1, INF);
        vector<char> was(m + 1, false);

        do {
            was[column] = true;
            int cur_row = matching[column];
            int delta = INF;
            int cur_column = 0;

            for (int j = 1; j <= m; ++j) {
                if (!was[j]) {
                    int cur = table[cur_row][j] - u[cur_row] - v[j];
                    if (cur < min_v[j]) {
                        min_v[j] = cur;
                        way[j] = column;
                    }
                    if (min_v[j] < delta) {
                        delta = min_v[j];
                        cur_column = j;
                    }
                }
            }

            for (int j = 0; j <= m; ++j) {
                if (was[j]) {
                    u[matching[j]] += delta;
                    v[j] -= delta;
                } else {
                    min_v[j] -= delta;
                }
            }

            column = cur_column;
        } while (matching[column] != 0);

        do {
            int j1 = way[column];
            matching[column] = matching[j1];
            column = j1;
        } while (column);
    }

    for (int j = 1; j <= m; ++j) {
        ans[matching[j]] = j;
    }

    return {-v[0], ans};
}

void solve() {
}

void output() {
    pair<int, vector<int>> ans = hungry(table, n, m);
    out << ans.first << "\n";
    for (int i = 1; i <= n; ++i) {
        out << i << " " << ans.second[i] << "\n";
    }
}


int main() {
    input();
    solve();
    output();
    return 0;
}