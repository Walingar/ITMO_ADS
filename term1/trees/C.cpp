#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <random>
using namespace std;
int random() {
	return (int)(((double)rand() / RAND_MAX)*INT_MAX);
}
struct leaf {
	leaf* left;
	leaf* right;
	leaf* parent;
	int key;
	int priority;
	bool isnull;
	leaf() : isnull(true),left(NULL), right(NULL), parent(NULL), key(-1), priority(random()) {};
};
pair <leaf*, leaf*> split(leaf *a, int key) {
	if (a == NULL) {
		return{ NULL, NULL };
	}
	if (key > a->key) {
		pair <leaf*, leaf*> p = split(a->right, key);
		a->right = p.first;
		if (p.first) {
			p.first->parent = a;
		}
		return{ a,p.second };
	}
	pair <leaf*, leaf*> p = split(a->left, key);
	a->left = p.second;
	if (p.second) {
		p.second->parent = a;
	}
	return{ p.first,a };
}
leaf* merge(leaf *a, leaf *b) {
	if (a == NULL) {
		return b;
	}
	if (b == NULL) {
		return a;
	}
	if (a->priority > b->priority) {
		leaf* p = merge(a->right, b);
		a->right = p;
		if (p) {
			p->parent = a;
		}
		return a;
	}
	leaf* p = merge(a, b->left);
	b->left = p;
	if (p) p->parent = b;
	return b;
}
struct treap {
	leaf* root;
	treap() : root(NULL) {};
	leaf* search(leaf* v, int x) {
		if (v == NULL || x == v->key) {
			return v;
		}
		if (x < v->key) {
			return search(v->left, x);
		}
		return search(v->right, x);
	}
	leaf* minimum(leaf* v) {
		if (v->left == NULL) {
			return v;
		}
		minimum(v->left);
	}
	leaf* maximum(leaf* v) {
		if (v->right == NULL) {
			return v;
		}
		maximum(v->right);
	}
	void insert(leaf *& v, leaf* x) {
		if (v == nullptr) {
            v = x;
			return;
		}
		if (v->priority > x->priority){
            if (x->key < v->key) insert(v->left, x);
            else insert(v->right, x);
            return;
        }
        pair <leaf*, leaf*> p = split(v, x->key);
        x->left = p.first;
        x->right = p.second;
        v = x;
	}
	void del(leaf *&v, int x) {
        if (v == nullptr) return;
        if (x < v->key){
            del(v->left,x);
        }
        else if (x > v->key){
            del(v->right,x);
        }
        else{
            v = merge(v->left,v->right);
        }

    }
	leaf* next( int x) {
		leaf* current = this->root;
		leaf* successor = NULL;
		while (current != NULL) {
			if (current->key > x) {
				successor = current;
				current = current->left;
			}
			else current = current->right;
		}
		return successor;
	}
	leaf* prev( int x) {
		leaf* current = this->root;
		leaf* successor = NULL;
		while (current != NULL) {
			if (current->key < x) {
				successor = current;
				current = current->right;
			}
			else current = current->left;
		}
		return successor;
	}
};

int main() {
	srand(time(0));
	ifstream in("bst.in");
	ofstream out("bst.out");
	string s;
	int x;
	treap t;
	while (in >> s) {
		if (s == "insert") {
			in >> x;
			if (t.search(t.root, x) == NULL) {
				leaf* p = new leaf;
				p->key = x;
				t.insert(t.root, p);
			}
			//cout << "OK" << "\n";
		}
		if (s == "exists") {
			in >> x;
			leaf* p = t.search(t.root, x);
			if (p) out << "true" << "\n";
			else out << "false" << "\n";
		}
		if (s == "next") {
			in >> x;
			leaf* p = t.next( x);
			if (p) out << p->key << "\n";
			else out << "none" << "\n";
		}
		if (s == "prev") {
			in >> x;
			leaf* p = t.prev( x);
			if (p) out << p->key << "\n";
			else out << "none" << "\n";
		}
		if (s == "delete") {
			in >> x;
			if (t.search(t.root, x) != NULL) {
				t.del(t.root, x);
			}
		}
	}
	in.close();
	out.close();
	return 0;
}
