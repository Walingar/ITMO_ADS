#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <math.h>
 
using namespace std;
 
vector<int> strings;
string t, s;
int n, m, f;
string ans_s = "";
const unsigned int MAX_N = 1000000 + 50;
 
vector<pair<int, int>> ans;
//#define in cin
//#define out cout
ifstream in("search6.in");
ofstream out("search6.out");
 
int get_letter_index(char ch) {
    return ch - 'a';
}
 
class Node {
public:
    Node *next[30] = {nullptr};
    Node *links[30] = {nullptr};
    bool term;
    char letter_from_parrent;
    Node *parent;
    Node *suff_link;
    Node *nice_suff_link;
    vector<int> numb;
    int count;
    int left;
    int right;
 
    Node() {
        left = MAX_N;
        right = -1;
        count = 0;
        term = false;
        letter_from_parrent = -1;
        parent = nullptr;
        suff_link = nullptr;
        nice_suff_link = nullptr;
        numb = {};
    }
};
 
Node root;
 
Node *next(Node *cur, char ch);
 
Node *get_link(Node *cur) {
    if (!cur->suff_link) {
        if (cur == &root || cur->parent == &root)
            cur->suff_link = &root;
        else {
            cur->suff_link = next(get_link(cur->parent), cur->letter_from_parrent);
            if (cur->suff_link->term) {
                cur->nice_suff_link = cur->suff_link;
            } else {
                cur->nice_suff_link = cur->suff_link->nice_suff_link;
            }
        }
 
    }
    return cur->suff_link;
}
 
Node *next(Node *cur, char ch) {
    int i = get_letter_index(ch);
    if (!cur->links[i])
        if (cur->next[i])
            cur->links[i] = cur->next[i];
        else {
            if (cur == &root)
                cur->links[i] = &root;
            else
                cur->links[i] = next(get_link(cur), ch);
        }
    get_link(cur->links[i]);
    return cur->links[i];
}
 
void add_string(string &st, int numb) {
    Node *cur = &root;
    int i;
    for (auto ch: st) {
        i = get_letter_index(ch);
        if (cur->next[i] == nullptr) {
            cur->next[i] = new Node();
            cur->next[i]->parent = cur;
            cur->next[i]->letter_from_parrent = ch;
        }
        cur = cur->next[i];
    }
    cur->term = true;
    cur->numb.push_back(numb);
}
 
 
void input() {
    in >> n;
    for (int i = 0; i < n; ++i) {
        in >> s;
        strings.push_back((int)s.length());
        add_string(s, i);
    }
    ans.resize(n, {MAX_N, -1});
    in >> t;
}
 
void update(Node *cur, int i) {
    cur->left = min(cur->left, i);
    cur->right = max(cur->right, i);
}
 
map<Node *, bool> was;
 
void dfs(Node *v) {
    was[v] = true;
    for (auto to: v->links)
        if (to && !was[to]) {
            Node *temp = to;
            int left = to->left;
            int right = to->right;
            if (to->count)
                while (temp && temp != &root) {
                    if (temp->term)
                        for (auto num: temp->numb) {
                            ans[num].first = min(ans[num].first, left);
                            ans[num].second = max(ans[num].second, right);
                        }
                    temp = temp->nice_suff_link;
                }
            dfs(to);
        }
}
 
void solve() {
    Node *cur = &root;
    for (int i = 0; i < t.length(); ++i) {
        cur = next(cur, t[i]);
        cur->count = 1;
        update(cur, i);
    }
    dfs(&root);
}
 
void output() {
    for (int i = 0; i < n; ++i){
        out << (ans[i].first == MAX_N ? -1 : ans[i].first - strings[i] + 1) << " ";
        out << (ans[i].second == -1 ? -1 : ans[i].second - strings[i] + 1) << "\n";
    }
 
}
 
int main() {
    input();
    solve();
    output();
    return 0;
}