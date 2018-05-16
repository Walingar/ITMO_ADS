#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
int inf = 1000 * 1000 * 1000;
int min(std::vector <int> &t, int L, int R, int l, int r, int v) {
	if (r < L || l > R ) {
		return inf;
	}
	if (L == R) {
		return t[v];
	}
	int m = (L + R) / 2;
	if (L >= l && R <= r) {
		return t[v];
	}
	else {
		return std::min(min(t, L, m, l, r, 2 * v + 1), min(t, m + 1, R, l, r, 2 * v + 2));
	}
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
		else if (m+1 <= pos && pos <= R) {
			set(t, m+1, R, pos, val, 2 * v + 2);
		}
		t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
	}
	
}
void build(std::vector <int> &a, std::vector <int> &t, int L, int R, int v) {
	if (L == R) {
		t[v] = a[L];
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
	std::ifstream in("rmq.in");
	std::ofstream out("rmq.out");
	int n;
	in >> n;
	std::vector <int> a(n);
	std::vector <int> t(4*n,inf);
	for (int i = 0; i < n; i++) {
		in >> a[i];
	}
	build(a, t, 0, n - 1, 0);
	std::string s;
	while (in >> s)
	{
		if (s == "min") {
			int x, y;
			in >> x >> y;
			out << min(t, 0, n - 1, x - 1, y - 1, 0) << "\n";
		}
		else {
			int x, y;
			in >> x >> y;
			set(t, 0, n - 1, x - 1, y, 0);
		}
	}
	in.close();
	out.close();
	return 0;
}