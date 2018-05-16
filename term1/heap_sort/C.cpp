#include <fstream>
#include <vector>

void merge(std::vector<int>&a, int l1, int r1, int l2, int r2)
{
	std::vector <int> b;
	int l3 = l1;
	while (l1<r1 || l2<r2)
	{
		if (l1 == r1 || (l2<r2 && a[l2]<a[l1]))
		{
			b.push_back(a[l2]);
			l2++;
		}
		else
		{
			b.push_back(a[l1]);
			l1++;
		}
	}
	for (int i = 0; i<b.size(); i++)
	{
		a[l3 + i] = b[i];
	}
}

void sort(std::vector<int>&a, int l, int r)
{
	if (r - l>1)
	{
		sort(a, l, (l + r) / 2);
		sort(a, (l + r) / 2, r);
		merge(a, l, (l + r) / 2, (l + r) / 2, r);
	}
}


int main()
{
	std::ifstream fin("sort.in");
	std::ofstream fout("sort.out");
	int n;
	fin >> n;
	std::vector <int> a(n);
	for (int i = 0; i < n; i++)
	{
		fin >> a[i];
	}
	sort(a, 0, a.size());
	for (int i = 0; i < n; i++)
	{
		fout << a[i] << " ";
	}
	fin.close();
	fout.close();
	return 0;
}
