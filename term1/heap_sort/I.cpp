#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;
vector <pair <double, double> > a;
double l;
double res(double time)
{
	double ans = 0;
	double now = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (now + a[i].first < time)
		{
			now += a[i].first;
			ans += a[i].second * a[i].first;
		}
		else
		{
			ans += (time - now)*a[i].second;
			break;
		}
	}
	return ans;
}
bool prov(double m)
{
	double p = 0;
	double s = 0;
	for (int i = 0; i < a.size(); i++)
    {
        s+=a[i].first;
    }
	for (int i = 0; i < a.size(); i++)
	{
        p += a[i].first;
        if(p >= m)
        {
            double l1 = res(p) - res(p-m);
            double l2 = res(p + m) - res(p);
            if (p + m > s) l2 = l;
            if (l1 < l || l2 < l)
            {
                return false;
            }
        }
	}
    double temp1 = res(m);
    if (temp1 < l)
    {
        return false;
    }
	return true;
}

double search_ans()
{
	double r = 0, left = 0;
	for (int i = 0; i < a.size(); i++)
	{
		r += a[i].first;
	}
	while (r - left>0.00001)
	{
		double m = left + (r - left) / 2;
		if (prov(m))
		{
			r = m;
		}
		else
		{
			left = m;
		}
	}
	return r;
}

int main()
{
    ofstream fout("trains.out");
    ifstream fin("trains.in");
	fin >> l;
	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		double temp1, temp2;
		fin >> temp1 >> temp2;
		a.push_back(make_pair(temp1, temp2));
	}
	fout << fixed;
	fout << setprecision(10) << search_ans();
	fin.close();
	fout.close();
	return 0;
}
