#include <bits/stdc++.h>

using namespace std;
const string file_name = "rps2";

//#define inp cin
//#define out cout

ifstream inp(file_name + ".in");
ofstream out(file_name + ".out");

int r1, r2, s1, s2, p1, p2;

void input() {
    inp >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
}

void solve() {

}

void output() {
    out << max(0, max(p1 - p2 - s2, max(r1 - r2 - p2, s1 - s2 - r2)));
    // :)))))))))))))))))))))))))))
    // or determinative graph and search min cost flow there
}


int main() {
    input();
    solve();
    output();
    return 0;
}