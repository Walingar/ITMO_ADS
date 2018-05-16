#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <vector>
std::ofstream out("bureaucracy.out");
std::ifstream in("bureaucracy.in");
int main()
{
    std::queue <int> a;
    int n, m;
    in >> n >> m;
    int min = INT_MAX;
    int minus = 0;
    for (int i = 0; i < n; i++)
    {
        int temp;
        in >> temp;
        a.push(temp);
    }
    while (a.size() > 0 && m/a.size() !=0 ){
        int t = a.size();
        int now = m/a.size();
        for (int i = 0; i < t; i++){
            int temp = a.front();
            a.pop();
            if (temp - now > 0){
                a.push(temp - now);
            }
            if (temp - now < 0) m -= temp - now;
        }
        m -= now*t;
    }
    if (a.size() == 0){
        out << -1;
    }
    else
    {
        for (int i = 0; i < m ; i++)
        {
            int temp = a.front();
            a.pop();
            if (temp - 1 >0) a.push(temp-1);
        }
        if (a.size() == 0){
            out << -1;
            out.close();
            return 0;
        }
        out << a.size() << "\n";
        int t = a.size();
        for (int i = 0; i < t ; i++)
        {
            int temp = a.front();
            a.pop();
            out << temp << " ";
        }
    }
	in.close();
	out.close();
	return 0;
}
