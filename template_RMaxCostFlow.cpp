#include<bits/stdc++.h>

using ll = long long;

struct MCFGraph {
    struct Edge {
        int v, c, f;
        Edge(int v, int c, int f) : v(v), c(c), f(f) {}
    };
    const int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<ll> h, dis;
    std::vector<int> pre;
    bool dijkstra(int s, int t) {
        dis.assign(n, std::numeric_limits<ll>::max());
        pre.assign(n, -1);
        std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<>> que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            ll d = que.top().first;
            int u = que.top().second;
            que.pop();
            if (dis[u] < d) continue;
            for (int i : g[u]) {
                int v = e[i].v;
                int c = e[i].c;
                int f = e[i].f;
                if (c > 0 && dis[v] > d + h[u] - h[v] + f) {
                    dis[v] = d + h[u] - h[v] + f;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != std::numeric_limits<ll>::max();
    }
    MCFGraph(int n) : n(n), g(n) {}
    void addEdge(int u, int v, int c, int f) {
        g[u].push_back(e.size());
        e.emplace_back(v, c, f);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -f);
    }
    std::pair<int, ll> flow(int s, int t) {
        int flow = 0;
        ll cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            int aug = std::numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) aug = std::min(aug, e[pre[i]].c);
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += ll(aug) * h[t];
        }
        return std::make_pair(flow, cost);
    }
};

struct R_MaxFlow {
    MCFGraph g;

    int ss, tt, n;
    ll l_sum = 0;
    std::vector<int> extra;
    std::vector<int> need_check;
    explicit R_MaxFlow(int n_) : g(n_ + 3), n(n_), ss(n_ + 1), tt(n_ + 2), extra(n_ + 3) {}

    void addEdge(int u, int v, int l, int r, int f) {
        g.addEdge(u, v, r - l, f);
        extra[u] -= l;
        extra[v] += l;
        l_sum += 1ll * l * f;
    }

    std::tuple<int, ll, bool> check(int s = -1, int t = -1) {
        if(s != -1 && t != -1) {
            g.addEdge(t, s, std::numeric_limits<int>::max(), 0);
        }
        int sum = 0;
        for(int i = 0; i < n; i++) {
            if(extra[i] > 0) {
                need_check.push_back(g.e.size());
                sum += extra[i];
                g.addEdge(ss, i, extra[i], 0);
            } else if(extra[i] < 0) {
                g.addEdge(i, tt, -extra[i], 0);
            }
        }
        auto c = g.flow(ss, tt);
        for(auto id : need_check) {
            if(g.e[id].c != 0) {
                return {c.first, c.second + l_sum, false};
            }
        }
        return {c.first, c.second + l_sum, sum == c.first};
    }
};