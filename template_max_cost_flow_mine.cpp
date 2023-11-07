#include<bits/stdc++.h>

const int N = 50005;
const int M = 500005;

const int inf = 0x7fffffff;
struct edge {
    int f, t, v, c, next;
} g[M];
int head[N], n, m, start, to, flow[N], vis[N], cost[N], pre[N], tot = 1, ans1, ans2;

void link(int x, int y, int v, int c, int k = 0) {
    g[++tot] = edge{x, y, v, c, head[x]};
    head[x] = tot;
    g[++tot] = edge{y, x, k, -c, head[y]};
    head[y] = tot;
}

int spfa() {
    for (int i = 0; i <= n; i++) cost[i] = inf, flow[i] = 0;
    std::queue<int> q;
    q.push(start);
    vis[start] = 1, flow[start] = inf, cost[start] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int y, i = head[x]; i; i = g[i].next) {
            y = g[i].t;
            if (g[i].v > 0 && g[i].c + cost[x] < cost[y]) {
                pre[y] = i;
                flow[y] = std::min(flow[x], g[i].v);
                cost[y] = g[i].c + cost[x];
                if (!vis[y]) vis[y] = 1, q.push(y);
            }
        }
    }
    return flow[to];
}

void update() {
    ans1 += flow[to];
    ans2 += flow[to] * cost[to];
    for (int x = to, i, y; x != start; x = y) {
        i = pre[x];
        y = g[i].f;
        g[i].v -= flow[to];
        g[i ^ 1].v += flow[to];
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &start, &to);
    for (int x, y, v, c, i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &x, &y, &v, &c);
        link(x, y, v, c);
    }
    while (spfa()) {
        update();
    }
    printf("%d %d", ans1, ans2);
}