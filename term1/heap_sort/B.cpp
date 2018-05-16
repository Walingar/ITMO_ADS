#include <fstream>
#include <vector>
#include <string>
std::vector <int> b;
struct leaf
{
	int data;
	int pos;
	int numb;
};

void SiftUp(std::vector<leaf>& a, int i)
{
	leaf temp;
	while ((i - 1) / 2 >= 0 && a[i].data < a[(i - 1) / 2].data)
	{
		temp = a[(i - 1) / 2];
		a[(i - 1) / 2] = a[i];
		a[i] = temp;
		a[i].pos = i;
		b[a[i].numb] = i;
		i = (i - 1) / 2;
		a[i].pos = i;
		b[a[i].numb] = i;
	}
}

void SiftDown(std::vector<leaf>& a, int i)
{
	leaf temp;
	long long p = a.size();
	while (2 * i + 2 < p && (a[i].data >= a[2 * i + 1].data || a[i].data >= a[2 * i + 2].data))
	{
		if (a[2 * i + 1].data < a[2 * i + 2].data)
		{
			temp = a[2 * i + 1];
			a[2 * i + 1] = a[i];
			a[i] = temp;
			a[i].pos = i;
			b[a[i].numb] = i;
			i = 2 * i + 1;
			a[i].pos = i;
			b[a[i].numb] = i;

		}
		else
		{
			temp = a[2 * i + 2];
			a[2 * i + 2] = a[i];
			a[i] = temp;
			a[i].pos = i;
			b[a[i].numb] = i;
			i = 2 * i + 2;
			a[i].pos = i;
			b[a[i].numb] = i;
		}
	}
	if (2 * i + 2 >= p && 2 * i + 1 < p && a[i].data > a[2 * i + 1].data)
	{
		temp = a[2 * i + 1];
		a[2 * i + 1] = a[i];
		a[i] = temp;
		a[i].pos = i;
		b[a[i].numb] = i;
		i = 2 * i + 1;
		a[i].pos = i;
		b[a[i].numb] = i;
	}
}




void push(std::vector<leaf>& a, leaf& x)
{
	a.push_back(x);
	SiftUp(a, a.size() - 1);
}


int extractMin(std::vector<leaf>& a)
{
	int ans = a[0].data;
	a[0] = a[a.size() - 1];
	a[0].pos = 0;
	b[a[0].numb] = 0;
	a.pop_back();
	SiftDown(a, 0);
	return ans;
}

void decrease(std::vector<leaf>& a, int x, int y)
{
	a[x].data = y;
	SiftUp(a, x);
}


int main()
{
	std::vector <leaf> a;
	std::string s;
	std::ifstream fin("priorityqueue.in");
	std::ofstream fout("priorityqueue.out");
	int t = -1;
	while (fin >> s)
	{
		int temp1, temp2, temp;
		b.push_back(-1);
		++t;
		if (s == "push")
		{
			leaf p;
			fin >> temp;
			p.data = temp;
			p.numb = t;
			b[t] = a.size() ;
			push(a, p);
		}
		else if (s == "extract-min")
		{
			if (a.size() > 0)
			{
				fout << extractMin(a) << "\n";
			}
			else
			{
				fout << "*" << "\n";
			}
		}
		else
		{
			fin >> temp1 >> temp2;
			decrease(a, b[temp1 - 1], temp2);
		}
	}
	fin.close();
	fout.close();
	return 0;
}
