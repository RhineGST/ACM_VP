#include<bits/stdc++.h>

const long long INF = 0x3fffffff;

template<typename Edge>
struct DirectedGraph {
    int node_size{}, edge_size{}, tarjan_tot{};
    std::vector<std::vector<Edge> > edge;
    std::vector<bool> vis;
    std::vector<int> dfn, low;

    void resize(int node_size_t) {
        this->node_size = node_size_t;
        edge.resize(node_size_t + 1);
    }

    void add_edge(Edge e) {
        edge_size++;
        edge[e.from].push_back(e);
//        std::swap(e.from, e.to);
//        edge[e.from].push_back(e);
    }

    template<typename T = decltype(Edge::w)>
    std::vector<T> dijkstra(int s) {
        std::vector<T> dis(node_size + 1, -1);
        using Pos = std::pair<T, int>;
        std::priority_queue<Pos, std::vector<Pos>, std::greater<>> q;
        q.emplace(0ll, s);
        while(!q.empty()) {
            auto [d, x] = q.top();
            q.pop();
            if(dis[x] != -1) {
                continue;
            }
            else {
                dis[x] = d;
            }
            for(const Edge &e : edge[x]) {
                if(dis[e.to] != -1) {
                    continue;
                }
                q.emplace(d + e.w, e.to);
            }
        }
        return dis;
    }
};

struct Edge {
    int from, to;
    long long w;
};

DirectedGraph<Edge> g;
using std::cin, std::cout, std::endl;

int main() {
    int n;
    cin >> n;
    int s = 1, t = 2;
    g.resize(n * n + 2);
    auto getId = [&](int x, int y) {
        if(y < 0 || x >= n) {
            return s;
        }
        else if(x < 0 || y >= n) {
            return t;
        }
        else {
            return y * n + x + t + 1;
        }
    };

    for(int x, i = 0; i <= n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> x;
            g.add_edge({getId(i, j), getId(i - 1, j), x});
        }
    }
    for(int x, i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) {
            cin >> x;
            g.add_edge({getId(i, j - 1), getId(i, j), x});
        }
    }
    for(int x, i = 0; i <= n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> x;
            g.add_edge({getId(i - 1, j), getId(i, j), x});
        }
    }
    for(int x, i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) {
            cin >> x;
            g.add_edge({getId(i, j), getId(i, j - 1), x});
        }
    }
    auto dis = g.dijkstra(s);
    cout << dis[t] << endl;
}