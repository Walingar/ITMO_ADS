#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    vector <pair <int, int> > a;
    vector <int> ans(4);
    vector <int> cnt(4);
    vector <int> last(4);
    ofstream fout("style.out");
    ifstream fin("style.in");
    for (int i = 0; i < 4; i++)
    {
        int l;
        fin >> l;
        for (int j = 0; j < l; j++)
        {
            int temp;
            fin >> temp;
            a.push_back(make_pair(temp, i));
        }
    }
    sort(a.begin(), a.end());

    int razn = 10000000, now = 0, left = 0;
    for (int i = 0; i < a.size(); i++)
    {
        cnt[a[i].second]++;
        if (cnt[a[i].second] == 1)
        {
            now++;
            //we need to have 4 subj in 'last' array
        }
        last[a[i].second] = a[i].first;
        while (cnt[a[left].second] > 1)
        {
            cnt[a[left].second]--;
            left++;
        }
        if (now == 4 && (a[i].first - a[left].first) < razn)
        {
            razn = a[i].first - a[left].first;
            for (int j = 0; j < 4; j++)
                ans[j] = last[j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        fout << ans[i] << ' ';
    }
    fout.close();
    fin.close();
    return 0;
}
