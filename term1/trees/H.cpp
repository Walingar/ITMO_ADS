#include <fstream>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
int N = 1000 * 1000 * 1000 + 7;
struct rect {
	int x1, x2, y1, y2;
	rect(int x1 = -1000001, int y1 = -1000001, int x2 = 1000001, int y2 = 1000001) :x1(x1), y1(y1), x2(x2), y2(y2) {};
	int s() {
		return(((long long)(this->x2 - this->x1)*(long long)(this->y2 - this->y1)) % N);
	}
	bool is0() {
		if (this->x2 == this->x1 || this->y2 == this->y1) {
			return true;
		}
		return false;
	}
};
rect merge(rect a, rect b) {
	if (a.y2 < b.y1 || a.y1 > b.y2 || a.x1 > b.x2 || a.x2 < b.x1)
	{
		rect ans(0, 0, 0, 0);
		return ans;
	}
	else {
		rect ans;
		ans.y1 = max(a.y1, b.y1);
		ans.x1 = max(a.x1, b.x1);
		ans.y2 = min(a.y2, b.y2);
		ans.x2 = min(a.x2, b.x2);
		return ans;
	}
}
rect a[128][128];
rect t[128][128][8][8];
int logs[128];
void create_logs() {
	for (int i = 0; i < 128; i++) {
		logs[i] = floor(log2(i));
	}
}
int n, m;
rect I0(0, 0, 0, 0);
rect I;
int ans = 0;
void build() {
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			for (int i = 0; i <= n - (1 << a); i++) {
				for (int j = 0; j <= m - (1 << b); j++) {
					if (a > 0) {
						t[i][j][a][b] = merge(t[i][j][a - 1][b], t[i + (1 << (a - 1))][j][a - 1][b]);
					}
					else if (b > 0){
						t[i][j][a][b] = merge(t[i][j][a][b - 1], t[i][j + (1 << (b - 1))][a][b - 1]);
					}
				}
			}	
		}
	}
}

int get(int x1, int y1, int x2, int y2) {
	int la = logs[x2 - x1];
	int lb = logs[y2 - y1];
	rect ans = merge(t[x1][y1][la][lb], t[x2 - (1 << la) + 1][y2 - (1 << lb) + 1][la][lb]);
	ans = merge(ans, t[x1][y2 - (1 << lb) + 1][la][lb]);
	ans = merge(t[x2 - (1 << la) + 1][y1][la][lb], ans);
	return ans.s();
}
int main() {
	create_logs();
	ofstream out("pail.out");
	ifstream in("pail.in");
	in >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x1, x2, y1, y2;
			in >> x1 >> y1 >> x2 >> y2;
			a[i][j].x1 = min(x1, x2);
			a[i][j].y1 = min(y1, y2);
			a[i][j].x2 = max(x1, x2);
			a[i][j].y2 = max(y1, y2);
			t[i][j][0][0] = a[i][j];
		}
	}
	build();
	int q;
	in >> q;
	int ans = 0;
	vector <int> rq(4 * q + 1);
	int A, B, v;
	in >> A >> B >> v;
	rq[0] = v;
	for (int i = 1; i <= 4 * q; i++) {
		rq[i] = ((long long)A*rq[i - 1] + B) % N;
		if (i % 4 == 0) {
			int x1, x2, y1, y2;
			x1 = min(rq[i - 3] % n, rq[i - 1] % n);
			y1 = min(rq[i - 2] % m, rq[i] % m);
			x2 = max(rq[i - 3] % n, rq[i - 1] % n);
			y2 = max(rq[i - 2] % m, rq[i] % m);
			ans = ((long long)ans + get(x1, y1, x2, y2))%N;
		}
	}
	out << ans;
	in.close();
	out.close();
	return 0;
}