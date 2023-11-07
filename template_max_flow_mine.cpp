#include<bits/stdc++.h>

const long long INF = 0x3fffffff;

namespace EK {
    const int N = 200;
    const int M = 5005;

    struct {
        int t, next;
        long long v;
    } tr[M << 1];

    int head[N], dis[N], c_head[N], n, m, start, to, tot = 1;
    long long ans;
    std::queue<int> q;

    void link(int x, int y, long long z) {
        tr[++tot] = {y, head[x], z};
        head[x] = tot;
        tr[++tot] = {x, head[y], 0};
        head[y] = tot;
    }

    int bfs() {
        for (int i = 0; i <= std::max(to, n); i++) {
            dis[i] = 0, c_head[i] = head[i];
        }
        while (!q.empty()) q.pop();
        q.push(start);
        dis[start] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int y, i = head[x]; i; i = tr[i].next) {
                y = tr[i].t;
                if (dis[y] || tr[i].v == 0) continue;
                q.push(y);
                dis[y] = dis[x] + 1;
            }
        }
        return dis[to];
    }

    long long dfs(int x, long long w) {
        if (x == to) {
            return w;
        }
        long long sum = 0;
        for (int y, i = c_head[x]; i && sum < w; i = tr[i].next) {
            y = tr[i].t;
            c_head[x] = i;
            if (dis[y] != dis[x] + 1) continue;
            long long t = dfs(y, std::min(w - sum, tr[i].v));
            if (t) tr[i].v -= t, tr[i ^ 1].v += t, sum += t;
        }
        return sum;
    }

    long long flow(int start_t, int to_t) {
        ans = 0;
        start = start_t;
        to = to_t;
        while (bfs()) {
            ans += dfs(start, INF);
        }
        return ans;
    }
}

using namespace EK;

int main(void) {
    scanf("%d%d%d%d", &n, &m, &start, &to);
    for (int x, y, i = 1; i <= m; i++) {
        long long z;
        scanf("%d%d%lld", &x, &y, &z);
        link(x, y, z);
    }
    printf("%lld", flow(start, to));
}