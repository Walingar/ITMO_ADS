#include <fstream>
#include <string>
#include <stack>
std::ofstream out("decode.out");
std::ifstream in("decode.in");


int main()
{
	std::stack <char> ans;
	std::string s;
	in >> s;
	ans.push(s[0]);
	for (int i = 1; i < s.length(); i++)
	{
		if (ans.size() > 0 && ans.top() == s[i]) {
			ans.pop();
		}
		else
		{
			ans.push(s[i]);
		}
	}
	s = "";
	while (ans.size() > 0) {
		s += ans.top();
		ans.pop();
	}
	for (int i = s.length()-1; i >= 0; i--)
    {
        out << s[i];
    }
	out.close();
	in.close();
	return 0;
}
