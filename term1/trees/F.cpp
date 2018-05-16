
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
int inf = 1000 * 1000 * 1000;
std::vector <int> pos(1000 * 1000);
int search(std::vector <int> &t, int L, int R, int l, int r, int v) {
    if (r < L || l > R) {
        return inf;
    }
    if (t[v] == 1) {
        return inf;
    }

    if (L == R) {
        if (t[v] == 0) {
            return pos[v];
        }
        else {
            return inf;
        }
    }
    int m = (L + R) / 2;
        int ans = search(t, L, m, l, r, 2 * v + 1);
        if (ans == inf) ans = search(t, m + 1, R, l, r, 2 * v + 2);
        return ans;
}
void set(std::vector <int> &t, int L, int R, int pos, int val, int v) {
    if (L == R) {
        t[v] = val;
    }
    else {
        int m = (L + R) / 2;
        if (L <= pos && pos <= m) {
            set(t, L, m, pos, val, 2 * v + 1);
        }
        else if (m + 1 <= pos && pos <= R) {
            set(t, m + 1, R, pos, val, 2 * v + 2);
        }
        t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
    }
}
void build(std::vector <int> &a, std::vector <int> &t, int L, int R, int v) {
    if (L == R) {
        t[v] = a[L];
        pos[v] = L;
    }
    else {
        int m = (L + R) / 2;
        build(a, t, L, m, 2 * v + 1);
        build(a, t, m + 1, R, 2 * v + 2);
        t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
    }
}
int main()
{
    std::ifstream in("parking.in");
    std::ofstream out("parking.out");
    int n, m;
    in >> n >> m;
    std::vector <int> a(n, 0);
    std::vector <int> t(4 * n, inf);
    build(a, t, 0, n - 1, 0);
    std::string s;
    for (int i = 0; i < m; i++) {
        in >> s;
        if (s == "enter") {
            int x;
            in >> x;
            int ans = search(t, 0, n - 1, x - 1, n - 1, 0);
            if (ans != inf) {
                out << ans + 1 << "\n";
            }
            else {
                ans = search(t, 0, n - 1, 0, x - 1, 0);
                out << ans + 1 << "\n";
            }
            set(t, 0, n - 1, ans, 1, 0);
        }
        else {
            int ans;
            in >> ans;
            set(t, 0, n - 1, ans - 1, 0, 0);
        }
    }
    in.close();
    out.close();
    return 0;
}
