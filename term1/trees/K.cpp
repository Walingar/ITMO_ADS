#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
int inf = 0;
int summ(std::vector <int> &t, int L, int R, int l, int r, int v) {
	if (r < L || l > R) {
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
		return summ(t, L, m, l, r, 2 * v + 1) + summ(t, m + 1, R, l, r, 2 * v + 2);
	}
}
void set(std::vector <int> &t, int L, int R, int pos, int val, int v) {
	if (L == R) {
		t[v] += val;
		return;
	}
	else {
		int m = (L + R) / 2;
		if (L <= pos && pos <= m) {
			set(t, L, m, pos, val, 2 * v + 1);
		}
		else if (m + 1 <= pos && pos <= R) {
			set(t, m + 1, R, pos, val, 2 * v + 2);
		}
		t[v] = t[2 * v + 1] + t[2 * v + 2];
	}

}
struct man {
	int come;
	int out;
	int pos;
};
struct WhenInOut {
	int when;
	int t;
	man *who;
};
void rightpos(std::vector <man*> &a, std::vector <man> &b) {
	for (int i = 0; i < b.size(); i++) {
		a.push_back(&b[i]);
	}
	std::sort(a.begin(), a.end(), [](const man *a, const man *b) {
		return (a->out < b->out);
	});
	for (int i = 0; i < b.size(); i++) {
		a[i]->pos = i;
	}
}
int main()
{
	std::ifstream in("taxibus.in");
	std::ofstream out("taxibus.out");
	int n;
	in >> n;
	std::vector < man > inp(n);
	std::vector <WhenInOut> wio(2 * n);
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		in >> inp[i].come >> inp[i].out;
		wio[2 * i].when = inp[i].come;
		wio[2 * i].t = 1;
		wio[2 * i].who = &inp[i];
		wio[2 * i + 1].when = inp[i].out;
		wio[2 * i + 1].t = 0;
		wio[2 * i + 1].who = &inp[i];
	}
	std::vector <man*> inp1;
	rightpos(inp1,inp);
	std::string answer;
	for (int i = 0; i < n; i++) {
		answer += std::to_string(inp[i].pos + 1) + " ";
	}
	std::sort(wio.begin(), wio.end(), [](const WhenInOut& a, const WhenInOut& b) {
		return (a.when < b.when);
	});
	std::vector <int> t(4 * n, inf);
	for (int i = 0; i < 2 * n; i++) {
		if (wio[i].t == 1) {
			ans += summ(t, 0, n - 1, 0, wio[i].who->pos,0);
			set(t, 0, n - 1, wio[i].who->pos, 1, 0);
		}
		else {
			set(t, 0, n - 1, wio[i].who->pos, -1, 0);
		}
	}
	out << ans << "\n" << answer;
	in.close();
	out.close();
	return 0;
}
