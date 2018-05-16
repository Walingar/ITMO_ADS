#include <bits/stdc++.h>

using namespace std;
const string file_name = "assignment";

#define inp cin
#define out cout

//ifstream inp(file_name + ".in");
//ofstream out(file_name + ".out");

const int MAX_N = 1000 + 5;
const int MAX_K = 30 + 2;
int INF = INT_MAX;

int n, p, k;

vector<vector<int>> edges(MAX_N, vector<int>());

vector<vector<int>> costs(MAX_N, vector<int>(MAX_K, -1));
vector<vector<vector<int>>> dp(MAX_N, vector<vector<int>>(MAX_K, vector<int>(MAX_K, 0)));

void input() {
    inp >> n >> k >> p;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            int cost;
            inp >> cost;
            costs[i][j] = cost;
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        int from, to;
        inp >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
}

vector<int> u(MAX_N + 1);
vector<int> v(MAX_K + 1);
vector<int> matching(MAX_K + 1);
vector<int> way(MAX_K + 1);
vector<int> min_v(MAX_K + 1, INF);
vector<char> was(MAX_K + 1, false);

int hungry(vector<vector<int>> &table, int n, int m) {
    u.assign(n + 1, 0);
    v.assign(m + 1, 0);
    matching.assign(m + 1, 0);
    way.assign(m + 1, 0);

    for (int row = 1; row <= n; ++row) {
        matching[0] = row;
        int column = 0;

        min_v.assign(m + 1, INF);
        was.assign(m + 1, false);

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

    return -v[0];
}


vector<vector<int>> children(MAX_N, vector<int>());

vector<char> was_dfs(MAX_N, false);

void create_normalize_tree(int v) {
    was_dfs[v] = true;
    for (int to: edges[v]) {
        if (!was_dfs[to]) {
            children[v].push_back(to);
            create_normalize_tree(to);
        }
    }
    if (children[v].empty()) {
        for (int color = 1; color <= k; ++color) {
            for (int parent = 0; parent <= k; ++parent) {
                dp[v][color][parent] = costs[v][color];
            }
        }
    }
}

vector<vector<int>> table = vector<vector<int>>(MAX_N + 2, vector<int>(MAX_K + 2));

int dfs(int v) {
    int min_cost = INF;
    for (int to: children[v]) {
        dfs(to);
    }
    for (int parent_color = 1; parent_color <= k; ++parent_color)
        for (int color = 1; color <= k; ++color) {
            if (children[v].size() > 0) {
                dp[v][color][parent_color] = p + costs[v][color];
            }

            for (int child: children[v]) {
                int child_cost = INF;
                for (int child_color = 1; child_color <= k; ++child_color) {
                    child_cost = min(child_cost, dp[child][child_color][color]);
                }
                dp[v][color][parent_color] += child_cost;
            }

            if (0 < children[v].size() && children[v].size() <= k - 1 ||
                (v == 1 && children[v].size() <= k)) {
                for (int i = 0; i < children[v].size(); ++i) {
                    for (int child_color = 1; child_color <= k; ++child_color) {
                        if (child_color == parent_color && v != 1) {
                            table[i + 1][child_color] = INF;
                        } else {
                            table[i + 1][child_color] = dp[children[v][i]][child_color][color];
                        }
                    }
                }
                dp[v][color][parent_color] = min(dp[v][color][parent_color],
                                                 hungry(table, children[v].size(), k) + costs[v][color]);
            }
            min_cost = min(min_cost, dp[v][color][parent_color]);
        }
    return min_cost;
}

void solve() {
    create_normalize_tree(1);

    dfs(1);
    int ans = INF;
    for (int color = 1; color <= k; ++color) {
        ans = min(ans, dp[1][color][1]);
    }
    out << ans;
}

void output() {
}


int main() {
    input();
    solve();
    output();
    return 0;
}