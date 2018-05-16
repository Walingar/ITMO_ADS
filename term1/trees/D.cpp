#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
struct matr{
    matr():a11(1),a12(0),a21(0),a22(1){};
    int a11;
    int a12;
    int a21;
    int a22;
};
matr I0;
matr mult(matr a,matr b,int r){
    matr ans;
    ans.a11 = ((a.a11*b.a11)%r + (a.a12 * b.a21)%r)%r;
    ans.a12 = ((a.a11*b.a12)%r + (a.a12 * b.a22)%r) % r;
    ans.a21 = ((a.a21*b.a11)%r + (a.a22 * b.a21)%r) % r;
    ans.a22 = ((a.a21*b.a12)%r + (a.a22 * b.a22)%r) % r;
	return ans;
}
matr count(std::vector <matr> &t, int L, int R, int l, int r, int v,int mod) {
    if (r < L || l > R ) {
        return I0;
    }
    if (L == R) {
        return t[v];
    }
    int m = (L + R) / 2;
    if (L >= l && R <= r) {
        return t[v];
    }
    else {
        return mult(count(t, L, m, l, r, 2 * v + 1, mod), count(t, m + 1, R, l, r, 2 * v + 2, mod), mod);
    }
}

void build(std::vector <matr> &a, std::vector <matr> &t, int L, int R, int v,int r) {
    if (L == R) {
        t[v] = a[L];
    }
    else {
        int m = (L + R) / 2;
        build(a, t, L, m, 2 * v + 1, r);
        build(a, t, m + 1, R, 2 * v + 2, r);
        t[v] = mult(t[2 * v + 1], t[2 * v + 2], r);
    }
}

int main()
{
    std::ifstream in("crypto.in");
    std::ofstream out("crypto.out");
    int r, n, m;
    in >> r >> n >> m;
    std::vector <matr> a(n);
    std::vector <matr> t(4*n, I0);
    for (int i = 0; i < n; i++){
        matr p;
        in >> p.a11 >> p.a12 >> p.a21 >> p.a22;
        a[i] = p;
    }
    build(a, t, 0, n-1, 0, r);
    for (int i = 0; i < m; i++){
        int x,y;
        in >> x >> y;
        matr temp = count(t,0,n-1,x-1,y-1,0,r);
        out << temp.a11 << " " << temp.a12 << "\n";
        out << temp.a21 << " " << temp.a22 << "\n";
        out << "\n";
    }
    in.close();
    out.close();
    return 0;
}
