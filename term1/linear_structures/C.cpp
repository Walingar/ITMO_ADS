#include <fstream>
#include <string>
#include <stack>
#include <stdlib.h>
std::ofstream out("postfix.out");
std::ifstream in("postfix.in");


int main()
{
	std::stack <int> a;
	std::string s;
	int x,y;
	while  (in >> s)
    {
        if (s == "+"){
            x = a.top();
            a.pop();
            y = a.top();
            a.pop();
            a.push(x+y);
        }
        else if (s == "-"){
            x = a.top();
            a.pop();
            y = a.top();
            a.pop();
            a.push(y - x);
        }
        else if (s == "*"){
            x = a.top();
            a.pop();
            y = a.top();
            a.pop();
            a.push(x*y);
        }
        else{
            a.push(atoi(s.c_str()));
        }
    }
    out << a.top();
	out.close();
	in.close();
	return 0;
}
