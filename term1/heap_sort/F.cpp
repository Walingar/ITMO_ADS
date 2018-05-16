#include <fstream>
#include <string>
#include <vector>
int main()
{
    std::ifstream fin("antiqs.in");
	std::ofstream fout("antiqs.out");
    int n;
    fin >> n;
    std::vector <int> a(n);
    for (int i=0; i<n;i++)
    {
        a[i] = i+1;
    }
    for (int i=2; i<n;i++)
    {
        int temp = a[i];
        a[i] = a[i/2];
        a[i/2] = temp;
    }
    for (int i=0; i<n;i++)
    {
        fout << a[i] << " ";
    }
    fin.close();
	fout.close();
	return 0;
}
