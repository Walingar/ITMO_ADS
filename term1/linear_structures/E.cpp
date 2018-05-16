#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <vector>
std::ofstream out("formation.out");
std::ifstream in("formation.in");
struct queue_cell
{
	queue_cell() : next(NULL),prev(NULL),data(1) {};
	int data;
	queue_cell *next;
	queue_cell *prev;
};
queue_cell *first = new queue_cell();

struct queue
{
	queue() :head(first){};
	queue_cell *head;
    void left(int i, int j, std::vector <queue_cell*>& path){
        queue_cell *srch = path[j];
        queue_cell *p = new queue_cell();
        p->data  = i;
        if (srch->prev){
            srch->prev->next = p;
            p->prev = srch->prev;
            p->next = srch;
            srch->prev = p;
        }
        else{
            srch->prev = p;
            p->next = srch;
            this->head = p;
        }
        path[i] = p;
    }
    void right(int i, int j, std::vector <queue_cell*>& path){
        queue_cell *srch = path[j];
        queue_cell *p = new queue_cell();
        p->data  = i;
        if (srch->next){
            srch->next->prev = p;
            p->prev = srch;
            p->next = srch->next;
            srch->next = p;
        }
        else{
            srch->next = p;
            p->prev = srch;
        }
        path[i] = p;

    }
    void leave(int i, std::vector <queue_cell*>&path){
        queue_cell *p = path[i];
        if (p == this->head){
            this->head = p->next;
            this->head->prev = NULL;
        }
        else if (!p->next){
            p->prev->next = NULL;
        }
        else{
            p->next->prev = p->prev;
            p->prev->next = p->next;
        }
    }
    void name(int i, std::vector <queue_cell*>& path){
        queue_cell *p = path[i];
        if (p->prev) out << p->prev->data;
        else out << 0;
        out << " ";
        if (p->next) out << p->next->data;
        else out << 0;
        out << "\n";
    }
};
int main()
{
    queue a;
    int n,m;
    in >> n >> m;
    std::string s;
    std::vector <queue_cell*> path(n+1);
    path[1] = first;
    for (int i = 0; i < m; i++){
        in >> s;
        if (s == "left"){
            int x,y;
            in >> x >> y;
            a.left(x,y,path);
        }
        if (s=="right"){
            int x,y;
            in >> x >> y;
            a.right(x,y,path);
        }
        if (s=="name"){
            int x;
            in >> x;
            a.name(x,path);
        }
        if (s=="leave"){
            int x;
            in >> x;
            a.leave(x,path);
        }
    }
	in.close();
	out.close();
	return 0;
}
