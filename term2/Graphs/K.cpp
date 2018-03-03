//
// Created by Walingar on 06.03.2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>

int n, m, fromPos, toPos;
std::string s;
std::ifstream in("shortpath.in");
std::ofstream out("shortpath.out");
using namespace std;

struct edge {
    int from;
    int to;
    int w;

    edge(int x, int y, int z) {
        from = x;
        to = y;
        w = z;
    }
};

vector<vector<edge>> edges;
vector<pair<int, bool>> d;
vector<int> was;

pair<int, bool> counting(int x) {
    //out.print(x + " ");
    was[x] = 1;
    if (x == fromPos) {
        return {0, true};
    }
    for (int i = 0; i < edges[x].size(); i++) {
        if (was[edges[x][i].to] != 0) {
            if (d[x].first > d[edges[x][i].to].first + edges[x][i].w) {
                if (d[edges[x][i].to].second || !d[x].second)
                    d[x] = {d[edges[x][i].to].first + edges[x][i].w, d[edges[x][i].to].second};
            }
        } else {
            pair<int, bool> temp = counting(edges[x][i].to);
            if (temp.second) {
                d[x] = {min(d[x].first, temp.first + edges[x][i].w), true};
            }
        }
    }
    was[x] = 2;
    return d[x];
}

void input() {
    in >> n >> m >> fromPos >> toPos;
    --fromPos;
    --toPos;
    for (int i = 0; i < n; i++) {
        vector<edge> temp;
        edges.push_back(temp);
        d.push_back({INT_MAX, false});
        was.push_back(0);
    }
    d[fromPos] = {0, true};
    for (int i = 0; i < m; i++) {
        int x, y, z;
        in >> x >> y >> z;
        --x, --y;
        edges[y].push_back(edge(y, x, z));
    }
}

int main() {
    int n, m;
    input();
    pair<int, bool> j = counting(toPos);
    if (j.second) {
        out << j.first;
    } else {
        out << "Unreachable";
    }
    return 0;
}