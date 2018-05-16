#include <fstream>
#include <string>
#include <stack>
std::ofstream out("brackets.out");
std::ifstream in("brackets.in");


int main()
{
	std::stack <char> ans;
	std::string s;
	std::string answer = "YES";
	in >> s;
	for (int i = 0; i < s.length(); i++)
	{
        if (s[i] == '[' || s[i] == '{' || s[i] == '('){
                ans.push(s[i]);
            }
        else
        {
            if (ans.size() == 0)
            {
                answer = "NO";
                break;
            }
            else
            {
                if (s[i] == '}' && ans.top() == '{'){
                    answer = "YES";
                    ans.pop();
                }
                else if (s[i] == ']' && ans.top() == '['){
                    answer = "YES";
                    ans.pop();
                }
                else if (s[i] == ')'&& ans.top() == '('){
                    answer = "YES";
                    ans.pop();
                }
                else{
                    answer = "NO";
                    break;
                }
            }
        }
	}
	if (ans.size() == 0)
    {
        out << answer;
    }
    else{
        out << "NO";
    }
	out.close();
	in.close();
	return 0;
}
