#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <vector>
std::ofstream out("saloon.out");
std::ifstream in("saloon.in");
int main()
{
    std::queue <int> ans;
    int n;
    in >> n;
    std::vector <int> answer(n,0);
    std::queue <int> s;
    for (int i = 0; i < n; i++){
        int hour, minut, toler;
        in >> hour >> minut>> toler;
        int now = hour*60 + minut;
        while(ans.size() > 0 && ans.front() + 20 <= now){
            s.push(ans.front()+20);
            ans.pop();
        }
        if(ans.size() > toler)
        {
            answer[i] = now;
        }
        else{
            if (ans.size() == 0){
                ans.push(hour*60+minut);
            }
            else{
                ans.push(ans.front()+20*ans.size());
            }

        }
    }
    while(ans.size() > 0){
        s.push(ans.front()+20);
        ans.pop();
    }
    for(int i =0 ; i < n; i++){
        if(answer[i] == 0){
            out << s.front()/60 << " " << s.front()%60 << "\n";
            s.pop();
        }
        else{
            out << answer[i]/60 << " " << answer[i]%60 << "\n";
        }
    }
	in.close();
	out.close();
	return 0;
}
