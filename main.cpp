#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int LN = 19;
constexpr int N = 1e5 + 5;
stack<int> winner_list, need_power;
struct Info {
    long long sum = 0;
    int min_val = LN + 1;
    int min_const = LN + 1;
    Info() : sum(0), min_val(LN + 1), min_const(LN + 1) {}

    bool test_loss(int R) {
        return (min_val < R) || (min_const < R);
    }
};

Info info[1 << (LN + 1)][2];
bool vis[1 << (LN + 1)][2], deg[1 << (LN + 1)];
int lg[1 << LN], val[N], at[N], constant_winner[1 << LN];
std::vector<unsigned char> deg_input[LN];

Info MergeCore(const Info &x, const Info &y, int R) {
    bool loss = (y.min_val < R) || (y.min_const < R);
    if(loss) {
        auto ans = x;
        ans.min_val = std::min(ans.min_val, std::max(R, y.min_val));
        if(y.min_const >= R) {
            ans.min_const = std::min(ans.min_const, std::max(R, y.min_const));
        }
        ans.sum += y.sum;
        return ans;
    } else {
        return y;
    }
}

Info Merge(const Info &x, const Info &y, int R, bool fl) {
    if(fl) {
        return MergeCore(x, y, R);
    } else {
        return MergeCore(y, x, R);
    }
}

Info ask(int x, int l, int r, int lim) {
    if(r <= lim) {
        if(vis[x][0]) {
            return info[x][0];
        } else {
            vis[x][0] = true;
            if(l == r) {
                info[x][0].min_const = val[l];
            } else {
                int mid = (l + r) >> 1;
                info[x][0] = Merge(ask(x << 1, l, mid, lim), ask(x << 1 | 1, mid + 1, r, lim), lg[r - l + 1], deg[x]);
            }
            return info[x][0];
        }
    } else if(lim < l) {
        if(vis[x][1]) {
            return info[x][1];
        } else {
            vis[x][1] = true;
            if(l == r) {
                info[x][1].sum = l;
                info[x][1].min_val = val[l];
            } else {
                int mid = (l + r) >> 1;
                info[x][1] = Merge(ask(x << 1, l, mid, lim), ask(x << 1 | 1, mid + 1, r, lim), lg[r - l + 1], deg[x]);
            }
            return info[x][1];
        }
    } else {
        int mid = (l + r) >> 1;
        auto lv = ask(x << 1, l, mid, lim);
        auto rv = ask(x << 1 | 1, mid + 1, r, lim);
        auto R = lg[r - l + 1];
        if((deg[x] && mid <= lim && rv.test_loss(R)) || (!deg[x] && mid <= lim && !lv.test_loss(R))) {
            winner_list.push(constant_winner[x << 1]);
        } else {
            winner_list.push(-1);
        }
        if(!deg[x] && mid <= lim && !lv.test_loss(R)) {
            need_power.push(LN + 1);
        } else if((deg[x] && mid <= lim) || (!deg[x] && mid > lim)) {
            need_power.push(R);
        } else {
            need_power.push(0);
        }
        return Merge(lv, rv, lg[r - l + 1], deg[x]);
    }
}

int getAns() {
    int ans = 0, sum_need = 0;
    while(!winner_list.empty()) {
        auto winner = winner_list.top(); winner_list.pop();
        auto need = need_power.top(); need_power.pop();
        cout << winner << ' ';
        if(winner != -1 && val[winner] >= sum_need) {
            ans += winner;
        }
        sum_need = std::max(sum_need, need);
    }
    cout << "ans end" << endl;
    return ans;
}

void build(int x, int l, int r, int d, int num) {
    if(l == r) {
        return;
    }
    deg[x] = deg_input[d][num];
    int mid = (l + r) >> 1;
    build(x << 1, l, mid, d + 1, num * 2);
    build(x << 1 | 1, mid + 1, r, d + 1, num * 2 + 1);
}

void clear(int x, int l, int r, int n) {
    if(l > n) {
        return;
    }
    vis[x][0] = false;
    info[x][0] = {};
    if(l == r) {
        constant_winner[x] = l;
        return;
    }
    int mid = (l + r) >> 1;
    clear(x << 1, l, mid, n);
    clear(x << 1 | 1, mid + 1, r, n);
    if(r <= n) {
        auto lc = constant_winner[x << 1];
        auto rc = constant_winner[x << 1 | 1];
        auto R = lg[r - l + 1];
        if(deg[x]) {
            constant_winner[x] = (val[rc] >= R ? rc : lc);
        } else {
            constant_winner[x] = (val[lc] >= R ? lc : rc);
        }
    }
}

bool get01() {
    char ch = cin.get();
    while(ch != '0' && ch != '1') {
        ch = cin.get();
    }
    return ch == '1';
}

int main() {
//    freopen("color2.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, K;
    cin >> n >> m;
    std::vector<int> query(m);
    for(K = 0; (1 << K) < n; K++);
    for(int i = 1; i <= n; i++) {
        cin >> at[i];
    }
    lg[0] = -1;
    for(int i = 2; i <= (1 << K); i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(auto & x : query) {
        cin >> x;
    }
    for(int i = K - 1; i >= 0; i--) {
        string str;
        deg_input[i].resize(1 << i);
        for(auto & x : deg_input[i]) {
            x = get01();
        }
    }
    build(1, 1, (1 << K), 0, 0);
    int T;
    cin >> T;
    while(T--) {
        std::array<int, 4> X{};
        for(auto & x : X) {
            cin >> x;
        }
        for(int i = 1; i <= n; i++) {
            val[i] = std::min(at[i] ^ X[i & 3], K);
        }
        clear(1, 1, 1 << K, n);
        long long sum = 0;
        for(int i = 0; i < m; i++) {
            int log_2 = lg[query[i] - 1] + 1;
            auto ans = ask(1 << (K - log_2), 1, 1 << log_2, query[i]).sum;
            ans += getAns();
            if(query[i] == (query[i] & -query[i])) {
                ans += constant_winner[1 << (K - log_2)];
            }
            cout << "ans: " << ans << endl;
            sum ^= 1ll * (i + 1) * ans;
        }
        cout << sum << endl;
    }
}

/**
5 5
0 0 0 0 0
1 2 3 4 5
1001
10
1
4
2 1 0 0
1 2 1 0
0 2 3 1
2 2 0 1
*/