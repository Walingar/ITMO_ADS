#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <vector>
std::ofstream out("hospital.out");
std::ifstream in("hospital.in");


struct queue_cell
{
	queue_cell() : next(NULL),prev(NULL),data(1) {};
	int data;
	queue_cell *next;
	queue_cell *prev;
};

queue_cell *middle = new queue_cell;

struct queue
{
	queue() :head(NULL), tail(NULL), size(0) {};
	queue_cell *head;
	queue_cell *tail;
	int size;
    void push(int x){
        this->size += 1;
        queue_cell *p = new queue_cell;
        p->next = tail;
        if (this->tail)
        {
            this->tail->prev = p;
        }
        this->tail = p;
        p->data = x;
        if (this->head == NULL)
        {
            this->head = p;
            middle = p;
        }
        if (middle->prev){
            if(this->size % 2 != 0){
                middle = middle->prev;
            }
        }
    }
    int pop(){
        int ans = this->head->data;
        if (this->head->prev)
        {
            this->head->prev->next = NULL;
            queue_cell *p = this->head;
            this->head = this->head->prev;
            delete p;
            this->size -= 1;
            if (size > 0 && middle->prev){
                if(this->size % 2 != 0){
                    middle = middle->prev;
                }
            }
            return ans;
        }
        else
        {
            this->head = NULL;
            this->size = 0;
            middle = NULL;
            return ans;
        }
    }
    void push_mid(int x){
        if (this->size <= 1){
            this->push(x);
            return;
        }
        queue_cell *p = new queue_cell();
        p->data  = x;
        this->size++;
        if (middle->prev){
            middle->prev->next = p;
            p->next = middle;
            p->prev = middle->prev;
            middle->prev = p;
        }
        else{
            middle->prev = p;
            p->next = middle;
        }
        if (this->size % 2 != 0)
        {
            middle = p;
        }
    }

};
int main()
{
    queue a;
    std::string s;
    int n;
    in >> n;
    for (int i = 0; i < n; i++){
        in >> s;
        if (s == "+"){
            int x;
            in >> x;
            a.push(x);
        }
        else if (s == "*"){
            int x;
            in >> x;
            a.push_mid(x);
        }
        else{
            out << a.pop() << "\n";
        }
    }
	in.close();
	out.close();
	return 0;
}
