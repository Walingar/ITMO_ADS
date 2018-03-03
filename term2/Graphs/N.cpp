#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

string fileName = "fire";
ofstream out(fileName + ".out");
ifstream in(fileName + ".in");
int n, m;
unsigned int MAX_N = 1000;
vector<vector<int>> edges(2 * MAX_N);
vector<vector<int>> backEdges(2 * MAX_N);
vector<int> color(MAX_N, 0);
vector<bool> was(MAX_N, false);
vector<int> order;
vector<int> components;
int ans = 0;
vector<string> st;
int ans1 = 0, ans2 = 0;
map<string, int> a;

void input() {
    cin >> n >> m;
    for (int i = 0; i < 2 * n; i++) {
        string x;
        cin >> x;
        a["+" + x] = i++;
        a["-" + x] = i;
        st.push_back(x);
        st.push_back(x);
    }
    for (int i = 0; i < m; ++i) {
        string x, y, z;
        cin >> x >> y >> z;
        edges[a[x]].push_back(a[z]);
        backEdges[a[z]].push_back(a[x]);
        if (x[0] == '+' && z[0] == '+') {
            edges[a["-" + z.substr(1, z.length())]].push_back(a["-" + x.substr(1, x.length())]);
            backEdges[a["-" + x.substr(1, x.length())]].push_back(a["-" + z.substr(1, z.length())]);
        } else if (x[0] == '+' && z[0] == '-') {
            edges[a["+" + z.substr(1, z.length())]].push_back(a["-" + x.substr(1, x.length())]);
            backEdges[a["-" + x.substr(1, x.length())]].push_back(a["+" + z.substr(1, z.length())]);
        } else if (x[0] == '-' && z[0] == '+') {
            edges[a["-" + z.substr(1, z.length())]].push_back(a["+" + x.substr(1, x.length())]);
            backEdges[a["+" + x.substr(1, x.length())]].push_back(a["-" + z.substr(1, z.length())]);
        } else {
            edges[a["+" + z.substr(1, z.length())]].push_back(a["+" + x.substr(1, x.length())]);
            backEdges[a["+" + x.substr(1, x.length())]].push_back(a["+" + z.substr(1, z.length())]);
        }
    }
}


set<string> b;
int start = 0;

void dfs1(int v) {
    was[v] = true;
    for (auto to: edges[v])
        if (!was[to])
            dfs1(to);
    order.push_back(v);
}

void dfs2(int v, int cl) {
    components[v] = cl;
    for (auto to: backEdges[v])
        if (components[to] == -1)
            dfs2(to, cl);

}

void output() {
    for (int i = 0; i < 2 * n; ++i)
        if (components[i] == components[++i]) {
            cout << "-1";
            return;
        }
    for (int i = 0; i < 2 * n; ++i) {
        if (components[i] > components[++i]) {
            b.insert(st[i]);
        }
    }
    cout << b.size() << "\n";
    for (auto i:b) cout << i << "\n";
}

void solve() {
    was.assign(2 * n, false);
    for (int i = 0; i < 2*n; ++i)
        if (!was[i])
            dfs1(i);

    components.assign(2 * n, -1);
    for (int i = 0, j = 0; i < 2 * n; ++i) {
        int v = order[2*n - i - 1];
        if (components[v] == -1)
            dfs2(v, j++);
    }


}

int main() {
    input();
    solve();
    output();
    return 0;
}