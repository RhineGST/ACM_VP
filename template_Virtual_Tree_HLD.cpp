#include <bits/stdc++.h>

using ll = long long;
const int N = 5e5 + 5;
using std::cin, std::cout, std::endl;

std::vector<std::pair<int, ll>> tr[N];

int size[N], fa[N], deep[N], son[N], top[N];
long long cost[N];

namespace Cut {
    void dfs1(int x, int p, int d, ll v) {
        deep[x] = d;
        size[x] = 1;
        fa[x] = p;
        son[x] = 0;
        cost[x] = v;
        for(auto [y, val] : tr[x]) {
            if(y == p) {
                continue;
            }
            dfs1(y, x, d + 1, std::min(v, val));
            size[x] += size[y];
            if(size[y] > size[son[x]]) {
                son[x] = y;
            }
        }
    }

    void dfs2(int x, int t) {
        top[x] = t;
        if(son[x]) {
            dfs2(son[x], t);
        }
        for(auto [y, val] : tr[x]) {
            if(y == son[x] || y == fa[x]) {
                continue;
            }
            dfs2(y, y);
        }
    }
}

namespace Work {

    struct Node {
        int id, top_id;
        ll val;
        explicit Node(int x, ll val) : val(val) {
            id = x;
            top_id = top[x];
        }

        bool operator< (const Node& y) const {
            if(deep[top_id] != deep[y.top_id]) {
                return deep[top_id] < deep[y.top_id];
            }
            else if(top_id != y.top_id) {
                return top_id < y.top_id;
            }
            else {
                return deep[id] < deep[y.id];
            }
        }
    };

    ll work(const std::vector<int>& point_list) {
        std::priority_queue<Node> q;
        for(auto x : point_list) {
            q.emplace(x, cost[x]);
        }
        while(!q.empty()) {
            auto [x, top_id, x_val] = q.top();
            q.pop();
            while(!q.empty() && q.top().top_id == top_id) {
                auto next = q.top();
                x_val = std::min(x_val + next.val, cost[next.id]);
                x = next.id;
                q.pop();
            }
            x_val = std::min(x_val, cost[x]);
            x = top[x];
            if(x == 1) {
                return x_val;
            }
            else {
                q.emplace(fa[x], x_val);
            }
        }
        return 0ll;
    }
}

//每次询问给定k个点，询问断开这k个点和根连接的最小代价

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for(int x, y, z, i = 1; i < n; i++) {
        cin >> x >> y >> z;
        tr[x].emplace_back(y, z);
        tr[y].emplace_back(x, z);
    }
    Cut::dfs1(1, 0, 1, 0x7ffffffffffll);
    Cut::dfs2(1, 1);

    int q;
    cin >> q;
    for(int i = 1; i <= q; i++) {
        int sz;
        cin >> sz;
        std::vector<int> query_list(sz, 0);
        for(auto &x : query_list) {
            cin >> x;
        }
        cout << Work::work(query_list) << endl;
    }
}