#include <fstream>
#include <string>
#include <vector>
std::vector <std::string> csort(std::vector <std::string>&a, int p)
{
    std::vector <int> counts(256);
    std::vector <std::string> ans(a.size());
    for (int i = 0; i<a.size(); i++)
    {
        counts[(int)a[i][p]]++;
    }
    for (int i = 1; i < counts.size(); i++)
    {
        counts[i] += counts[i-1];
    }
    for (int i=a.size()-1; i >=0; i--)
    {
        int numb = counts[(int)a[i][p]];
        ans[numb-1] = a[i];
        counts[(int)a[i][p]]--;
    }
    return ans;
}

int main()
{
    std::ifstream fin("radixsort.in");
	std::ofstream fout("radixsort.out");
    int n,k,m;
    fin >> n >> m >> k;
    std::vector <std::string> a(n);
    for(int i = 0; i < n; i++)
    {
        fin >> a[i];
    }
    for(int i = 0; i < k; i++)
    {
         a = csort(a,m-1-i);
    }
    for(int i = 0; i<n; i++)
    {
        fout << a[i] << "\n";
    }
	fin.close();
	fout.close();
	return 0;
}
