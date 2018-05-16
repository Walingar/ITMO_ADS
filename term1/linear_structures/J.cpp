#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <vector>
#include <deque>
std::ofstream out("kenobi.out");
std::ifstream in("kenobi.in");
std::vector <std::deque <int> > a(2);
int now = 0;

void add(int x){
        a[now].push_front(x);
		if (a[now].size() - 2 == a[(now + 1) % 2].size()) {
			a[(now + 1) % 2].push_front(a[now].back());
            a[now].pop_back();
		}
}

void take(){
        if (a[now].size() == 0) return;
		a[now].pop_front();
		if (a[now].size() < a[(now + 1) % 2].size()) {
			a[now].push_back(a[(now + 1) % 2].front());
			a[(now + 1) % 2].pop_front();
		}
}

void mother(){
        if (a[now].size() == 0) return;
		now = (now + 1) % 2;
		if (a[now].size() < a[(now + 1) % 2].size()) {
			a[now].push_back(a[(now + 1) % 2].front());
			a[(now + 1) % 2].pop_front();
		}
}


int main()
{
    int n;
    in >> n;
    std::string s;
    for (int i = 0; i < n; i++){
        in >> s;
        if (s == "add"){
            int x;
            in >> x;
            add(x);
        }
        else if (s == "take"){
            take();
        }
        else{
            mother();
        }
    }
    out << a[0].size() + a[1].size() << "\n";
    if (a[0].size() + a[1].size() == 0) return 0;
    while (a[(now + 1) % 2].size()!=0) {
        out << a[(now + 1) % 2].back() << " ";
        a[(now + 1) % 2].pop_back();
    }
    while (a[now].size() > 1) {
        out << a[now].back() << " ";
        a[now].pop_back();
    }
    out << a[now].back() << "\n";
	in.close();
	out.close();
	return 0;
}
