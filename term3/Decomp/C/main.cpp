#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
 
using namespace std;
 
#define in cin
#define out cout
 
//string fileName = "mail";
//ofstream out(fileName + ".out");
//ifstream in(fileName + ".in");
int n, l, m;
const int maxN = 100000 + 50;
 
class Node {
public:
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    int count = 1;
    int value = 1;
    pair<int, int> key = {-1, -1};
 
    Node(Node *p, pair<int, int> k, int v) {
        parent = p;
        key.first = k.first;
        key.second = k.second;
        value = v;
    }
 
};
 
map<pair<int, int>, long long> toPriority;
map<pair<int, int>, Node *> toTree;
 
int count(Node *x) {
    return x ? x->count : 0;
}
 
void updateCount(Node *x) {
    if (x)
        x->count = count(x->left) + count(x->right) + 1;
}
 
int getX(Node *x) {
    int ans = count(x->left);
    while (x) {
        if (x->parent && x->parent->right == x)
            ans += count(x->parent->left) + 1;
        x = x->parent;
    }
    return ans;
}
 
Node *getRoot(Node *x) {
    while (x->parent) {
        x = x->parent;
    }
    return x;
}
 
Node *merge(Node *left, Node *right) {
    if (!left)
        return right;
    if (!right)
        return left;
    if (toPriority[left->key] > toPriority[right->key]) {
        left->right = merge(left->right, right);
        if (left->right) left->right->parent = left;
        updateCount(left);
        left->parent = nullptr;
        return left;
    } else {
        right->left = merge(left, right->left);
        if (right->left) right->left->parent = right;
        updateCount(right);
        right->parent = nullptr;
        return right;
    }
}
 
 
pair<Node *, Node *> split(Node *root, int x) {
    if (!root)
        return {nullptr, nullptr};
    int l = count(root->left);
    if (l >= x) {
        pair<Node *, Node *> temp = split(root->left, x);
        root->left = temp.second;
        if (root->left) root->left->parent = root;
        updateCount(root);
        if (root) root->parent = nullptr;
        if (temp.first) temp.first->parent = nullptr;
        return {temp.first, root};
    }
    pair<Node *, Node *> temp = split(root->right, x - l - 1);
    root->right = temp.first;
    if (root->right) root->right->parent = root;
    updateCount(root);
    if (root) root->parent = nullptr;
    if (temp.second) temp.second->parent = nullptr;
    return {root, temp.second};
};
 
void doprint(Node *node) {
    if (!node) {
        return;
    }
    doprint(node->left);
    printf("%d %d \n", node->key.first, node->key.second);
    doprint(node->right);
}
 
void input() {
    in >> n >> m;
}
 
void solve() {
    for (int i = 0; i < n; ++i) {
        Node *temp = new Node(nullptr, {i, i}, 1);
        toPriority[{i, i}] = stoll(to_string(i) + to_string(i));
        toTree[{i, i}] = temp;
    }
}
 
void link(int v, int u) {
    Node *v_u = new Node(nullptr, {v, u}, 0);
    Node *u_v = new Node(nullptr, {u, v}, 0);
    toTree[{v, u}] = v_u;
    toTree[{u, v}] = u_v;
    toPriority[{u, v}] = stoll(to_string(u) + to_string(v));
    toPriority[{v, u}] = stoll(to_string(v) + to_string(u));
    Node *fdlg = getRoot(toTree[{u, u}]);
    int ge = getX(toTree[{u, u}]);
    pair<Node *, Node *> B = split(getRoot(toTree[{u, u}]), getX(toTree[{u, u}]));
    pair<Node *, Node *> A = split(getRoot(toTree[{v, v}]), getX(toTree[{v, v}]));
    Node *temp = merge(A.first, v_u);
    temp = merge(temp, B.second);
    temp = merge(temp, B.first);
    temp = merge(temp, u_v);
    temp = merge(temp, A.second);
}
 
 
void cut(int v, int u) {
    Node *v_u = toTree[{v, u}];
    Node *u_v = toTree[{u, v}];
    if (getX(u_v) < getX(v_u))
        swap(v_u, u_v);
    pair<Node *, Node *> temp1 = split(getRoot(v_u), getX(v_u));
    pair<Node *, Node *> temp2 = split(temp1.second, getX(v_u) + 1);
    pair<Node *, Node *> temp3 = split(getRoot(u_v), getX(u_v));
    pair<Node *, Node *> temp4 = split(temp3.second, getX(u_v) + 1);
    merge(temp1.first, temp4.second);
}
 
int isConnected(int v, int u) {
    return getRoot(toTree[{v, v}]) == getRoot(toTree[{u, u}]) ? 1 : 0;
}
 
 
void output() {
    string s;
    int v, u;
    for (int i = 0; i < m; ++i) {
        in >> s;
        in >> v >> u;
        --v, --u;
        if (s == "link") {
            //doprint(getRoot(toTree[{v, u}]));
            link(min(v, u), max(v, u));
        } else if (s == "cut") {
            cut(min(v, u), max(v, u));
        } else {
            out << isConnected(min(v, u), max(v, u)) << "\n";
        }
    }
}
 
 
int main() {
    input();
    solve();
    output();
    return 0;
}