#include "bits/stdc++.h"

const int maxn = 2e6 + 5;

template<typename Edge, int max_size>
struct UndirectedGraph {
    int node_size{}, edge_size{}, tarjan_tot{};
    std::vector<Edge> edge[max_size];
    bool vis[max_size];
    int dfn[max_size], low[max_size];

    void resize(int node_size_t) {
        this->node_size = node_size_t;
    }

    void add_edge(Edge e) {
        edge_size++;
        edge[e.from].push_back(e);
        std::swap(e.from, e.to);
        edge[e.from].push_back(e);
    }

    void tarjan_edge(int node, int in_edge) {
        dfn[node] = low[node] = ++tarjan_tot;
        for(auto &e : edge[node]) {
            const int to = e.to;
            if(dfn[to] == 0) {
                tarjan_edge(to, e.id);
                if(dfn[node] < low[to]) {
                    vis[e.id] = true;
                }
                low[node] = std::min(low[node], low[to]);
            }
            else if(e.id != in_edge) {
                low[node] = std::min(low[node], dfn[to]);
            }
        }
    }

    void tarjan_edge() {
        tarjan_tot = 0;
        for(int i = 1; i <= node_size; i++) {
            if(dfn[i] == 0) {
                tarjan_edge(i, 0);
            }
        }
    }

    void find_block() {
        std::vector<bool> vis_t(node_size + 1, false);
        std::vector<std::vector<int> > ans;
        std::function<void(int, int)> dfs = [&](int x, int block_id) -> void {
            ans[block_id].push_back(x);
            vis_t[x] = true;
            for(auto [from, to, id] : edge[x]) {
                if(vis_t[to] || vis[id]) {
                    continue;
                }
                dfs(to, block_id);
            }
        };
        for(int i = 1; i <= node_size; i++) {
            if(!vis_t[i]) {
                ans.emplace_back();
                dfs(i, (int)ans.size() - 1);
            }
        }
        std::cout << ans.size() << std::endl;
        for(auto &node_list : ans) {
            std::cout << node_list.size() << " ";
            for(auto node : node_list) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }
};

struct Edge {
    int from, to, id;
};

UndirectedGraph<Edge, maxn> graph;

//tarjan后给所有的割边在vis数组内标记为true

int main() {
    int n, m;
    std::cin >> n >> m;
    graph.resize(n);
    for(int x, y, i = 1; i <= m; i++) {
        std::cin >> x >> y;
        graph.add_edge({x, y, i});
    }
    graph.tarjan_edge();
    graph.find_block();
}