#include <fstream>
#include <string>
#include <stack>
#include <stdlib.h>
std::ofstream out("stack-min.out");
std::ifstream in("stack-min.in");

struct stuck_cell
{
	int data;
	int minim;
	stuck_cell *next;
};

struct stack
{
	stack(): head(NULL){};
	stuck_cell *head;
	void push(int x)
	{
		stuck_cell *p = new stuck_cell;
		p->next = this->head;
		p->data = x;
        if (!this->head || x < this->head->minim){
            p->minim = x;
        }
        else
        {
            p->minim = this->head->minim;
        }
        this->head = p;
	}
	void pop()
	{
		stuck_cell *p = this->head;
		this->head = p->next;
		delete p;
	}
};

int main()
{
    stack a;
    int com;
    int n;
    in >> n;
    for (int i = 0; i < n; i++){
        in >> com;
        if (com == 1){
            int temp;
            in >> temp;
            a.push(temp);
        }
        else if (com == 2){
            a.pop();
        }
        else{
            out << a.head->minim << "\n";
        }
    }
    in.close();
    out.close();
	return 0;
}
