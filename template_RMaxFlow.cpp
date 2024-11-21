#include<bits/stdc++.h>

using ll = long long;

template<class T = int>
struct MaxFlow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };

    int n;
    std::vector<_Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;

    MaxFlow() {}
    MaxFlow(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }

    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
};

struct R_MaxFlow {
    MaxFlow<int> g;

    int ss, tt, n;
    std::vector<int> extra;
    std::vector<int> need_check;
    explicit R_MaxFlow(int n_) : g(n_ + 3), n(n_), ss(n_ + 1), tt(n_ + 2), extra(n_ + 3) {}

    void addEdge(int u, int v, int l, int r) {
        g.addEdge(u, v, r - l);
        extra[u] -= l;
        extra[v] += l;
    }

    std::tuple<int, bool> check(int s = -1, int t = -1) {
        if(s != -1 && t != -1) {
            g.addEdge(t, s, std::numeric_limits<int>::max());
        }
        int sum = 0;
        for(int i = 0; i < n; i++) {
            if(extra[i] > 0) {
                need_check.push_back(g.e.size());
                sum += extra[i];
                g.addEdge(ss, i, extra[i]);
            } else if(extra[i] < 0) {
                g.addEdge(i, tt, -extra[i]);
            }
        }
        auto c = g.flow(ss, tt);
        return {c, sum == c};
    }
};