#include<bits/stdc++.h>

//using namespace std;
using ll = long long;

const ll maxn = 1e6 + 5;

const ll M = 91815541ll;

std::vector<int> tr[maxn];

int T, n, m;
int vis[maxn], top_t, flag, cir[maxn], size[maxn];

bool dfs(int x, int p) {
    if(vis[x]) {
        top_t = x;
        flag = true;
        return true;
    }
    vis[x] = 1;
    for(auto y : tr[x]) {
        if(y == p) {
            continue;
        }
        if(dfs(y, x)) {
            cir[x] = flag;
            if(x == top_t) {
                flag ^= 1;
            }
            return flag;
        }
    }
    return false;
}

ll tree_hash(int x, int p) {
    std::vector<ll> son_hash;
    size[x] = 1;
    for(auto y : tr[x]) {
        if(y == p || cir[y]) {
            continue;
        }
        son_hash.push_back(tree_hash(y, x));
        size[x] += size[y];
    }
    ll hash_ans = size[x];
    std::sort(son_hash.begin(), son_hash.end());
    ll index = 13333ll + (size[x] << 1);
    for(auto hash_v : son_hash) {
        hash_ans = (hash_ans + index * hash_v) % M;
        index++;
    }
    return hash_ans;
}

using std::cin, std::cout;

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int x, y, i = 1; i <= m; i++) {
            cin >> x >> y;
            tr[x].push_back(y);
            tr[y].push_back(x);
        }
        if(m == n - 1) {
            cout << "YES" << '\n';
        }
        else if(m > n) {
            cout << "NO" << '\n';
        }
        else {
            dfs(1, 0);
            bool fin = false;
            std::pair<ll, ll> hash_all{-1, -1};
            for(int x = 1; x <= n && (!fin); x++) {
                if(!cir[x]) {
                    continue;
                }
                for(auto y : tr[x]) {
                    if(cir[y]) {
                        ll hash_x = tree_hash(x, 0), hash_y = tree_hash(y, 0);
                        auto hash_v = std::make_pair(std::min(hash_x, hash_y), std::max(hash_x, hash_y));
                        if(hash_all.first < 0) {
                            hash_all = hash_v;
                        }
                        else if(hash_all != hash_v) {
                            fin = true;
                        }
                    }
                    if(fin) {
                        break;
                    }
                }
            }
//            cout << "fin\n";
            if(fin) {
                cout << "NO" << '\n';
            }
            else {
                cout << "YES" << '\n';
            }
        }
        for(int i = 1; i <= n; i++) {
            tr[i].clear();
            size[i] = 0;
            cir[i] = vis[i] = 0;
        }
    }
    return 0;
}
