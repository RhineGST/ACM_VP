#include<bits/stdc++.h>

const int N = 100005;
int n, m, ans[N];

std::vector<std::pair<int, int>> tr[N];
using std::cin, std::cout, std::endl;

namespace PointDivide {

    int vis[N], size[N], max_size[N], judge[10000005], dis[N], que[N];
    std::vector<int> dis_list;

    int get_root(int x, int p, int s) {
        int root = 0;
        std::function<void(int, int)> dfs = [&](int x, int p) {
            size[x] = 1;
            max_size[x] = 0;
            for (auto [y, v] : tr[x]) {
                if (vis[y] || y == p) {
                    continue;
                }
                dfs(y, x);
                size[x] += size[y];
                max_size[x] = std::max(max_size[x], size[y]);
            }
            max_size[x] = std::max(max_size[x], s - size[x]);
            if (!root || max_size[x] < max_size[root]) {
                root = x;
            }
        };
        dfs(x, p);
        return root;
    }

    void update(int x, int p) {
        if(dis[x] <= 1e7) {
            dis_list.push_back(dis[x]);
        }
        for (auto [y, v] : tr[x]) {
            if (vis[y] || y == p) {
                continue;
            }
            dis[y] = dis[x] + v;
            update(y, x);
        }
    }

    void solve(int x, int s) {
        vis[x] = 1;
        std::vector<int> temp_list;
        for (auto [y, v] : tr[x]) {
            if (vis[y]) continue;
            dis[y] = v;
            dis_list.clear();
            update(y, x);
            judge[0] = 1;
            for (auto dis_y : dis_list) {
                for (int k = 1; k <= m; k++) {
                    if (que[k] < dis_y) {
                        continue;
                    }
                    if (que[k] - dis_y == 0 || judge[que[k] - dis_y]) {
                        ans[k] = 1;
                    }
                }
            }
            temp_list.insert(temp_list.end(), dis_list.begin(), dis_list.end());
            for (auto dis_y : dis_list) {
                judge[dis_y] = 1;
            }
        }
        for (auto dis_t : temp_list) {
            judge[dis_t] = 0;
        }
        for (auto [y, v] : tr[x]) {
            if (vis[y]) {
                continue;
            }
            auto size_y = size[y] > size[x] ? s - size[x] : size[y];
            auto root = get_root(y, x, size_y);
            solve(root, size_y);
        }
    }
}

using namespace PointDivide;

//m个询问，每次询问树上有没有长度为k的路径

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int x, y, z, i = 1; i < n; i++) {
        cin >> x >> y >> z;
        tr[x].emplace_back(y, z);
        tr[y].emplace_back(x, z);
    }
    for (int x, i = 1; i <= m; i++) {
        cin >> x;
        que[i] = x;
    }
    auto root = get_root(1, 0, n);
    solve(root, n);
    for (int i = 1; i <= m; i++) {
        cout << (ans[i] ? "AYE" : "NAY") << endl;
    }
}