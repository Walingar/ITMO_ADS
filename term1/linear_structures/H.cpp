#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <vector>
std::ofstream out("hemoglobin.out");
std::ifstream in("hemoglobin.in");
int main()
{
    std::stack <int> a;
    int n;
    in >> n;
    char s;
    std::vector <int> summ(n + 1);
    for (int i=0; i< n; i++){
        in >> s;
        if (s == '+'){
            int x;
            in >> x;
            a.push(x);
            summ[a.size()] = summ[a.size()-1] + x;
        }
        else if ( s == '-'){
            out << a.top() << "\n";
            a.pop();
        }
        else{
            int k;
            in >> k;
            out << summ[a.size()] - summ[a.size() - k] << "\n";
        }
    }
	in.close();
	out.close();
	return 0;
}
