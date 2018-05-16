#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
long long inf = std::pow(10,18)-1;
std::vector <long long> d(1000 * 1000, 0);
std::vector <long long> pr(1000 * 1000, inf);
void propogate(std::vector <long long> &t,long long L, long long R, long long v) {
	if (pr[v] != inf) {
		pr[v * 2 + 1] = pr[v * 2 + 2] = pr[v];
		t[v * 2 + 1] = pr[v] + d[v];
		t[v * 2 + 2] = pr[v] + d[v];
		pr[v] = inf;
		d[v * 2 + 1] = d[v];
		d[v * 2 + 2] = d[v];
		d[v] = 0;
	}
	else {
		t[v * 2 + 1] += d[v];
		t[v * 2 + 2] += d[v];
		d[v * 2 + 1] += d[v];
		d[v * 2 + 2] += d[v];
		d[v] = 0;
	}
}
long long min(std::vector <long long> &t, long long L, long long R, long long l, long long r, long long v) {
	if (r < L || R < l) {
		return inf;
	}
	if (L == R) {
		return t[v];
	}
	if (L >= l && R <= r) {
		return t[v];
	}
	else {
		propogate(t, L, R, v);
		long long m = (L + R) / 2;
		return std::min(min(t, L, m, l, r, 2 * v + 1), min(t, m + 1, R, l, r, 2 * v + 2));
	}
}
void set(std::vector <long long> &t, long long L, long long R, long long l, long long r, long long v, long long val) {
	if (r < L || R < l) {
		return;
	}
	if (L == R) {
		d[v] = 0;
		pr[v] = inf;
		t[v] = val;
		return;
	}
	if (L >= l && R <= r) {
		d[v] = 0;
		t[v] = val;
		pr[v] = val;
	}
	else {
		propogate(t, L, R, v);
		long long m = (L + R) / 2;
		set(t, L, m, l, r, 2 * v + 1,val);
		set(t, m + 1, R, l, r, 2 * v + 2,val);
		t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
	}
}

void add(std::vector <long long> &t, long long L, long long R, long long l, long long r, long long v, long long val) {
	if (r < L || R < l) {
		return;
	}
	if (L == R) {
		t[v] += val;
		d[v] = 0;
		return;
	}
	if (L >= l && R <= r) {
		t[v] += val;
		d[v] += val;
	}
	else {
		propogate(t, L, R, v);
		long long m = (L + R) / 2;
		add(t, L, m, l, r, 2 * v + 1, val);
		add(t, m + 1, R, l, r, 2 * v + 2, val);
		t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
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
		t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
	}
}
int main()
{
	std::ifstream in("rmq2.in");
	std::ofstream out("rmq2.out");
	long long n;
	in >> n;
	std::vector <long long> a(n);
	std::vector <long long> t(4 * n, inf);
	for (long long i = 0; i < n; i++) {
		in >> a[i];
	}
	build(a, t, 0, n - 1, 0);
	std::string s;
	while (in >> s)
	{
		if (s == "min") {
			long long x, y;
			in >> x >> y;
			out << min(t, 0, n - 1, x - 1, y - 1, 0) << "\n";
		}
		else if (s=="set"){
			long long x, y, z;
			in >> x >> y >> z;
			set(t, 0, n - 1, x - 1, y - 1, 0, z);
		}
		else {
			long long x, y, z;
			in >> x >> y >> z;
			add(t, 0, n - 1, x - 1, y - 1, 0, z);
		}
	}
	in.close();
	out.close();
	return 0;
}
