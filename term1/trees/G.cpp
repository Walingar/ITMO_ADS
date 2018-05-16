#include<vector>
#include<fstream>
#include<algorithm>
#include<math.h>
#include<ctime>
using namespace std;
struct leaf {
	long long priority, size;
	long long sum, val;
	leaf* left;
	leaf* right;
	leaf(long long val) : val(val), sum(val*val), size(1), left(NULL), right(NULL) { priority = rand(); };
};
typedef pair<leaf*, leaf*> pll;

long long getSize(leaf*t) {
	return (t ? t->size : 0);
}

long long index(leaf*t) {
	return getSize(t->left) + 1;
}

long long getSum(leaf*t) {
	return (t ? t->sum : 0);
}

void update(leaf*t) {
	if (!t)
		return;
	t->size = getSize(t->left) + getSize(t->right) + 1;
	t->sum = getSum(t->left) + getSum(t->right) + (t->val)*(t->val);
}

leaf* merge(leaf*l, leaf*r) {
	if (!l)
		return r;
	if (!r)
		return l;
	if (l->priority > r->priority) {
		l->right = merge(l->right, r);
		update(l);
		return l;
	}
	else {
		r->left = merge(l, r->left);
		update(r);
		return r;
	}
}

pll split(leaf*t, long long k) {
	if (!t)
		return pll(NULL, NULL);
	pll ans;
	if (index(t) <= k) {
		ans = split(t->right, k - index(t));
		t->right = ans.first;
		ans.first = t;
	}
	else {
		ans = split(t->left, k);
		t->left = ans.second;
		ans.second = t;
	}
	update(t);
	return ans;
}

leaf* insert(leaf*t, long long i, long long x) {
	leaf*n = new leaf(x);
	if (!t) return n;
	pll p = split(t, i);
	t = merge(merge(p.first, n), p.second);
	return t;
}
leaf* del(leaf*t, long long i) {
	if (!t) return NULL;
	pll p = split(t, i - 1);
	pll p2 = split(p.second, 1);
	t = merge(p.first, p2.second);
	return t;
}
long long get(leaf*t, long long i) {
	if (!t)
		return 0;
	if (index(t) == i)
		return t->val;
	if (index(t) < i)
		return get(t->right, i - index(t));
	return get(t->left, i);
}
void set(leaf*t, long long i, long long val) {
	if (!t)
		return;
	if (index(t) == i)
		t->val += val;
	if (index(t) < i)
		set(t->right, i - index(t), val);
	if (index(t) > i)
		set(t->left, i, val);
	update(t);
}


int main() {
	srand(time(0));
	ofstream out("river.out");
	ifstream in("river.in");
	long long n, p;
	in >> n >> p;
	leaf*t = NULL;
	for (long long i = 0; i < n; i++) {
		long long temp;
		in >> temp;
		leaf*n = new leaf(temp);
		t = merge(t, n);
	}
	out << getSum(t) << "\n";

	long long k;
	in >> k;
	for (long long i = 0; i < k; i++) {
		long long x, pos;
		in >> x >> pos;
		if (x == 1) {
			long long val = get(t, pos);
			if (pos == 1) set(t, 2, val);
			else if (pos == getSize(t)) set(t, getSize(t) - 1, val);
			else {
				long long l = val / 2, r = val - l;
				set(t, pos - 1, l);
				set(t, pos + 1, r);
			}
			t = del(t, pos);
		}
		else {
			long long val = get(t, pos);
			long long l = val / 2, r = val - l;
			t = del(t, pos);
			t = insert(t, pos - 1, r);
			t = insert(t, pos - 1, l);
		}
		out << getSum(t) << "\n";
	}
	in.close();
	out.close();
	return 0;
}