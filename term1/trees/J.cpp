#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;
struct leaf {
	long long max;
	long long suff;
	long long preff;
	leaf() : max(0), suff(0), preff(0) {};
};
vector <leaf> t(2 * 1000000);
vector <long long> a(10000000);
void update(long long L, long long R, long long v) {
	t[v].max = std::max(t[2 * v + 1].max, t[2 * v + 2].max);
	t[v].max = std::max(t[v].max, t[2 * v + 1].suff + t[2 * v + 2].preff);
	long long m = (L + R) / 2;
	if (t[2 * v + 1].preff == m - L) {
		t[v].preff = t[2 * v + 1].preff + t[2 * v + 2].preff;
	}
	else {
		t[v].preff = t[2 * v + 1].preff;
	}
	if (t[2 * v + 2].suff == R - m) {
		t[v].suff = t[2 * v + 1].suff + t[2 * v + 2].suff;
	}
	else {
		t[v].suff = t[2 * v + 2].suff;
	}
}
void build(long long L, long long R, long long v) {
	if (R - L == 1) {
		if (a[L] == 1) {
			t[v].max = 1;
			t[v].preff = 1;
			t[v].suff = 1;
		}
		return;
	}
	long long m = (L + R) / 2;
	build(L, m, v * 2 + 1);
	build(m, R, v * 2 + 2);
	update(L, R, v);
}
long long getMax(long long L, long long R, long long l, long long r, long long v) {
	if (L >= r || l >= R) {
		return 0;
	}
	if (l <= L && R <= r) {
		return t[v].max;
	}
	long long m = (L + R) / 2;
	long long tmp1 = getMax(L, m, l, r, 2 * v + 1);
	long long tmp2 = getMax(m, R, l, r, 2 * v + 2);
	//-----------------------------------------
	long long preff = t[2 * v + 2].preff;
	preff = min((int)preff, (int)r - (int)m);
	long long suff = t[2 * v + 1].suff;
	suff = min((int)suff,(int)m - (int)l);
	return max(max(tmp1, tmp2), preff + suff);

}
void add(long long L, long long R, long long pos, long long val, long long v) {
	if (R - L == 1) {
		a[L] += val;
		if (a[L] == 1) {
			t[v].max = 1;
			t[v].preff = 1;
			t[v].suff = 1;
		}
		else {
			t[v].max = 0;
			t[v].preff = 0;
			t[v].suff = 0;
		}
		return;
	}
	long long m = (R + L) / 2;
	if (pos < m) add(L, m, pos, val, 2 * v + 1);
	else add(m, R, pos, val, 2 * v + 2);
	update(L, R, v);
}
int main()
{
	ifstream in("atoms.in");
	ofstream out("atoms.out");
	long long n;
	in >> n;
	vector <long long> input(n);
	for (long long i = 0; i < n; i++) {
		in >> input[i];
	}
	for (long long i = 1; i < n; i++) {
		a[i] = input[i] - input[i - 1];
	}
	a[0] = 0;
	build(0, n, 0);
	long long m;
	string s;
	in >> m;
	for (long long i = 0; i < m; i++) {
		in >> s;
		if (s == "+") {
			long long x, y, z;
			in >> x >> y >> z;
			--x;
			add(0, n, x, z, 0);
			if (y < n) {
				add(0, n, y, -z, 0);
			}
		}
		else {
			long long x, y;
			in >> x >> y;
			out << getMax(0, n, x, y, 0) + 1 << "\n";
		}
	}
	return 0;
}