#include "bits/stdc++.h"

const int maxn = 5e3 + 5;

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

    std::vector<int> find_block() {
        std::vector<int> ans(node_size + 1, false);
        int block_tot = 0;
        std::function<void(int, int)> dfs = [&](int x, int block_id) -> void {
            ans[x] = block_id;
            for(auto [from, to, id] : edge[x]) {
                if(ans[to] || vis[id]) {
                    continue;
                }
                dfs(to, block_id);
            }
        };
        for(int i = 1; i <= node_size; i++) {
            if(!ans[i]) {
                dfs(i, ++block_tot);
            }
        }
        ans[0] = block_tot;
        return ans;
    }
};

struct Edge {
    int from, to, id;
};

UndirectedGraph<Edge, maxn << 1> graph;
std::vector<int> tr[maxn];
int edge_num[maxn], node_num[maxn], size[maxn];

typedef long long ll;
const ll mod = 998244353;
int n, m;

ll dp[maxn][maxn];
ll pow2[maxn], p_pow2[maxn];
ll pow(ll x, ll y) {
    ll ans = 1ll;
    while(y) {
        if(y & 1ll) {
            ans = ans * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}

ll pow_2(ll y) {
    return pow2[y % n] * p_pow2[y / n] % mod;
}

void dfs(int x, int p) {
    edge_num[x] >>= 1;
    dp[x][node_num[x]] = pow(2ll, node_num[x] * (node_num[x] - 1) / 2 - edge_num[x]);
    size[x] = node_num[x];
    std::vector<ll> new_dp(maxn, 0);
    for(auto y : tr[x]) {
        if(y == p) {
            continue;
        }
        dfs(y, x);
        for(int i = size[x]; i <= node_num[x]; i++) {
            for(int j = 1; j <= node_num[y]; j++) {
                new_dp[i + j] = (new_dp[i + j] + dp[x][i] * dp[y][j] % mod * pow_2(i * j - 1)) % mod;
                new_dp[i] = (new_dp[i] - dp[x][i] * dp[y][j] + mod) % mod;
            }
        }
        node_num[x] += node_num[y];
        for(int i = size[x]; i <= node_num[x]; i++) {
            dp[x][i] = new_dp[i];
            new_dp[i] = 0;
        }
    }
}

int main() {
    std::cin >> n >> m;
    pow2[0] = 1ll;
    for(int i = 1; i <= n; i++) {
        pow2[i] = (pow2[i - 1] << 1) % mod;
    }
    p_pow2[0] = 1ll;
    for(int i = 1; i <= n; i++) {
        p_pow2[i] = (p_pow2[i - 1] * pow2[n]) % mod;
    }
    graph.resize(n);
    for(int x, y, i = 1; i <= m; i++) {
        std::cin >> x >> y;
        graph.add_edge({x, y, i});
    }
    graph.tarjan_edge();
    auto mark = graph.find_block();
    for(int i = 1; i <= n; i++) {
        node_num[mark[i]]++;
        for(auto [from, to, id] : graph.edge[i]) {
            if(mark[from] == mark[to]) {
                edge_num[mark[from]]++;
            }
            else {
                tr[mark[from]].push_back(mark[to]);
            }
        }
    }
    mark[0] = 0;
    dfs(1, 0);
    ll ans = 0;
    for(int i = 1; i <= node_num[1]; i++) {
        ans = (ans + dp[1][i]) % mod;
    }
    std::cout << ans << std::endl;
}