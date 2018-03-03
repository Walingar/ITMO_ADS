#include <fstream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
 
int z[1000000 + 50];
long long ans = 1;
string s;
ifstream in("cyclic.in");
ofstream out("cyclic.out");
 
void input() {
    in >> s;
    s += s;
}
 
void solve() {
    int left = 0, right = 0;
    for (int i = 1; i < s.length() / 2; ++i) {
        if (i <= right)
            z[i] = min(right - i, z[i - left]);
        while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] > right) {
            left = i;
            right = i + z[i] - 1;
        }
        if (i + z[i] < s.length() && s[i + z[i]] < s[z[i]]){
            //cerr << i << " ";
            ans++;
        }
    }
}
 
void output() {
    out << ans;
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}