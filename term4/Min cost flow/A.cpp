#include <bits/stdc++.h>

using namespace std;
const string file_name = "mincost";

//#define inp cin
//#define out cout

ifstream inp(file_name + ".in");
ofstream out(file_name + ".out");

struct Edge {
    int from;
    int to;
    long long flow;
    long long capacity;
    long long cost;
    int rev_id = -1;

    Edge() {

    }

    Edge(int from, int to, long long flow, long long capacity, long long cost) : from(from), to(to), flow(flow),
                                                                                 capacity(capacity), cost(cost) {
    }
};

const int MAX_N = 100 + 5;
const int MAX_M = 1000 + 5;
long long INF = LONG_LONG_MAX;

int s, t;
int n, m;
long long max_flow = 0;
long long min_cost = 0;
vector<vector<Edge>> edges(MAX_N, vector<Edge>());
vector<long long> d(MAX_N, INF);
vector<int> id(MAX_N, 0);
vector<Edge*> path(MAX_N);


void input() {
    inp >> n >> m;
    s = 1;
    t = n;
    int from, to;
    long long capacity, cost;
    for (int i = 0; i < m; ++i) {
        inp >> from >> to >> capacity >> cost;

        edges[from].push_back(Edge(from, to, 0, capacity, cost));
        edges[to].push_back(Edge(to, from, 0, 0, -cost));

        edges[from].back().rev_id = (int) edges[to].size() - 1;
        edges[to].back().rev_id = (int) edges[from].size() - 1;
    }
}

void levit() {
    deque<int> q;
    id.assign(n + 1, 0);
    d.assign(n + 1, INF);
    path.assign(n + 1, nullptr);

    d[s] = 0;
    q.push_back(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        id[v] = 2;

        for (auto &edge: edges[v]) {
            if (edge.flow < edge.capacity && d[edge.to] > d[edge.from] + edge.cost) {
                d[edge.to] = d[edge.from] + edge.cost;
                if (id[edge.to] == 0) {
                    q.push_back(edge.to);
                } else if (id[edge.to] == 2) {
                    q.push_front(edge.to);
                }
                path[edge.to] = &edge;
                id[edge.to] = 1;
            }
        }
    }
}

void solve() {
    while (true) {
        levit();
        if (d[t] == INF) {
            break;
        }

        long long delta = INF;
        for (int v = t; v != s; v = path[v]->from) {
            Edge* e = path[v];
            delta = min(delta, e->capacity - e->flow);
        }

        for (int v = t; v != s; v = path[v]->from) {
            Edge* e = path[v];
            Edge* e_rev = &edges[e->to][e->rev_id];

            e->flow += delta;
            e_rev->flow -= delta;

            min_cost += e->cost * delta;
        }

        max_flow += delta;
    }
}

void output() {
    out << min_cost;
}


int main() {
    input();
    solve();
    output();
    return 0;
}