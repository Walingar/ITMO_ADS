#include <bits/stdc++.h>

#define INF 10000000000

using namespace std;
int n, w;
auto dist = vector<long long>(10000, INF);

struct rect {
    rect() {

    }

    rect(long long x1, long long y1, long long x2, long long y2) : x1(x1), y1(y1), x2(x2), y2(y2) {

    }

    long long x1;
    long long x2;
    long long y1;
    long long y2;
};

long long distGet(rect r1, rect r2) {
    long long h = (r1.x1 <= r2.x1) ? r2.x1 - r1.x2 : r1.x1 - r2.x2;
    long long v = (r1.y1 <= r2.y1) ? r2.y1 - r1.y2 : r1.y1 - r2.y2;
    long long ans = max(h, v);
    if (ans < 0) {
        ans = 0;
    }
    return ans;
}

auto was = vector<bool>(10000, false);

void dijkstra(vector<vector<long long>> &vertex) {
    dist[0] = 0;
    for (int i = 0; i < n + 2; ++i) {
        long long v = -1;
        for (int j = 0; j < n + 2; ++j) {
            if (!was[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }
        was[v] = true;
        for (int u = 0; u < n + 2; ++u) {
            if (v != u) {
                long long d = vertex[v][u];
                if (dist[v] + d < dist[u]) {
                    dist[u] = dist[v] + d;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &w);
    auto vertex = vector<vector<long long>>(n + 2, vector<long long>(n + 2));
    auto rectangles = vector<rect>(n);
    for (int i = 0; i < n; ++i) {
        long long x1, y1, x2, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        rectangles[i] = rect(x1, y1, x2, y2);
    }
    vertex[0][n + 1] = w;
    vertex[n + 1][0] = w;
    for (int i = 0; i < n; ++i) {
        rect cur_rect = rectangles[i];
        long long min_y = min(cur_rect.y1, cur_rect.y2);
        long long max_y = max(cur_rect.y1, cur_rect.y2);
        vertex[0][i + 1] = vertex[i + 1][0] = w - max_y;
        vertex[n + 1][i + 1] = vertex[i + 1][n + 1] = min_y;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                vertex[i + 1][j + 1] = vertex[j + 1][i + 1] = distGet(cur_rect, rectangles[j]);
            }
        }
    }
    dijkstra(vertex);
    printf("%lld", (dist[n + 1] == INF) ? 0 : dist[n + 1]);
    return 0;
}