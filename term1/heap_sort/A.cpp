#include <fstream>

int main()
{
    std::ifstream fin("isheap.in");
    int n;
    fin >> n;
    int a[n];
    for(int i = 0; i < n; i++)
    {
        fin >> a[i];
    }
    fin.close();
    std::ofstream fout("isheap.out");
    for(int i = 0; i < n; i++)
    {
        if (2*i+1 < n && a[i] > a[2*i+1])
        {
            fout << "NO";
            fout.close();
            return 0;
        }
        else if(2*i+2 < n && a[i] > a[2*i+2])
        {
            fout << "NO";
            fout.close();
            return 0;
        }
    }
    fout << "YES";
    fout.close();
    return 0;
}
