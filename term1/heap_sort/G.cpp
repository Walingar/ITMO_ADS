#include <fstream>
#include <string>
#include <vector>
#include <cmath>
int main()
{
    std::ifstream fin("style.in");
	std::ofstream fout("style.out");
	int n;
	fin>> n;
	std::vector <int> a(n);
	for(int i = 0; i < n; i++)
    {
        fin >> a[i];
    }
    int m;
	fin>> m;
	std::vector <int> b(m);
	for(int i = 0; i < m; i++)
    {
        fin >> b[i];
    }
    int ans=std::abs(a[0]-b[0]),ansi=1,ansj=1;
    int i=0, j=0;
    while(i<n && j < m)
    {
        if (i<n && j<m && ans>std::abs(a[i]-b[j]))
        {
            ans = std::abs(a[i]-b[j]);
            ansi=i+1;
            ansj=j+1;
        }
        if (a[i]<b[j])
        {
            i++;
        }
        else if(a[i]==b[j])
        {
            ansi=i+1;
            ansj=j+1;
            break;
        }
        else
        {
            j++;
        }
        if (i<n && j<m && ans>std::abs(a[i]-b[j]))
        {
            ans = std::abs(a[i]-b[j]);
            ansi=i+1;
            ansj=j+1;
        }
    }
    //output
    fout << a[ansi-1] << " " << b[ansj-1];
    fin.close();
	fout.close();
	return 0;
}
