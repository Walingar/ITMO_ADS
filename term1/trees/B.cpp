#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
long long inf = 0;
long long min(std::vector <long long> &t, long long L, long long R, long long l, long long r, long long v) {
	if (r < L || l > R ) {
		return inf;
	}
	if (L == R) {
		return t[v];
	}
	long long m = (L + R) / 2;
	if (L >= l && R <= r) {
		return t[v];
	}
	else {
		return min(t, L, m, l, r, 2 * v + 1) + min(t, m + 1, R, l, r, 2 * v + 2);
	}
}
void set(std::vector <long long> &t, long long L, long long R, long long pos, long long val, long long v) {
	if (L == R) {
		t[v] = val;
	}
	else {
		long long m = (L + R) / 2;
		if (L <= pos && pos <= m) {
			set(t, L, m, pos, val, 2 * v + 1);
		}
		else if (m+1 <= pos && pos <= R) {
			set(t, m+1, R, pos, val, 2 * v + 2);
		}
		t[v] = t[2 * v + 1] + t[2 * v + 2];
	}
	
}
void build(std::vector <long long> &a, std::vector <long long> &t, long long L, long long R, long long v) {
	if (L == R) {
		t[v] = a[L];
	}
	else {
		long long m = (L + R) / 2;
		build(a, t, L, m, 2 * v + 1);
		build(a, t, m + 1, R, 2 * v + 2);
		t[v] = t[2 * v + 1] +  t[2 * v + 2];
	}
}
int main()
{
	std::ifstream in("rsq.in");
	std::ofstream out("rsq.out");
	long long n;
	in >> n;
	std::vector <long long> a(n);
	std::vector <long long> t(4*n,inf);
	for (long long i = 0; i < n; i++) {
		in >> a[i];
	}
	build(a, t, 0, n - 1, 0);
	std::string s;
	while (in >> s)
	{
		if (s == "sum") {
			long long x, y;
			in >> x >> y;
			out << min(t, 0, n - 1, x - 1, y - 1, 0) << "\n";
		}
		else {
			long long x, y;
			in >> x >> y;
			set(t, 0, n - 1, x - 1, y, 0);
		}
	}
	in.close();
	out.close();
	return 0;
}