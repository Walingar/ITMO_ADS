#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
int inf = std::pow(10, 9) + 1;
int ans = 0;
std::vector <int> d(1000 * 1000, 0);
void propogate(std::vector <int> &t, std::vector <int> &tm, int v) {
    t[v * 2 + 1] += d[v];
    t[v * 2 + 2] += d[v];
    tm[v * 2 + 1] += d[v];
    tm[v * 2 + 2] += d[v];
    d[v * 2 + 1] += d[v];
    d[v * 2 + 2] += d[v];
    d[v] = 0;
}


void kick(std::vector <int> &t, std::vector <int> &tm, int L, int R, int l, int r, int v, int val) {
    if (r < L || R < l) {
        return ;
    }
    if (L == R) {
        if (t[v] >= val) {
            --t[v];
            --tm[v];
            ++ans;
        }
        return;
    }
    if (L >= l && R <= r) {
        if (t[v] >= val) {
            --t[v];
            --d[v];
            --tm[v];
            ans += R - L + 1;
            return;
        }
    }
    propogate(t,tm, v);
    int m = (L + R) / 2;
    if (tm[2*v + 1] >= val) kick(t, tm, L, m, l, r, 2 * v + 1, val);
    if (tm[2*v + 2] >= val) kick(t, tm, m + 1, R, l, r, 2 * v + 2, val);
    t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
    tm[v] = std::max(tm[2 * v + 1], tm[2 * v + 2]);
}
void build(std::vector <int> &a, std::vector <int> &t, std::vector <int> &tm, int L, int R, int v) {
    if (L == R) {
        t[v] = a[L];
        tm[v] = a[L];
    }
    else {
        int m = (L + R) / 2;
        build(a, t, tm, L, m, 2 * v + 1);
        build(a, t, tm, m + 1, R, 2 * v + 2);
        t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
        tm[v] = std::max(tm[2 * v + 1], tm[2 * v + 2]);
    }
}
int main()
{
    std::ifstream in("candies.in");
    std::ofstream out("candies.out");
    int n;
    in >> n;
    std::vector <int> a(n);
    std::vector <int> t(4 * n, inf);
    std::vector <int> tm(4 * n, 0);
    for (int i = 0; i < n; i++) {
        in >> a[i];
    }
    std::sort(a.begin(), a.end());
    build(a, t, tm, 0, n - 1, 0);
    int m;
    in >> m;
    //int t = 0;
    for (int i = 0; i < m; i++) {
        int val;
        /*++t;
        i (t == 1000){
            for (int i = 0; i < n; i++){
                propogate(t,tm,i);
            }
            build(a, t, tm, 0, n - 1, 0);
        }*/
        in >> val;
        ans = 0;
        kick(t,tm, 0, n - 1, 0, n - 1, 0, val);
        out << ans << "\n";
    }
    in.close();
    out.close();
    return 0;
}
