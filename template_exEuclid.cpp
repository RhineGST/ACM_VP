//
// Created by GST49 on 2023/10/27.
//
#include "bits/stdc++.h"
using ll = long long;
const ll mod = 998244353ll;

struct Mat {
    const static int max_size = 5;
    int n, m;
    ll val[max_size][max_size];

    explicit Mat() = default;
    explicit Mat(int n, int m) : n(n), m(m) {
        memset(val, 0, sizeof(val));
        for(int i = 0; i < n; i++) {
            val[i][i] = 1;
        }
    }
    explicit Mat(int n, int m, const ll val_cp[max_size][max_size]) : n(n), m(m) {
        memcpy(val, val_cp, sizeof(val));
    }

    ll* operator[](int x) {
        return val[x];
    }

    Mat operator* (const Mat& y) const {
        const Mat& x = *this;
        Mat ans(x.n, y.m);
        for(int i = 0; i < ans.n; i++) {
            for(int j = i + 1; j < ans.m; j++) {
                for(int k = i; k <= j; k++) {
                    ans[i][j] = (ans[i][j] + x.val[i][k] * y.val[k][j]) % mod;
                }
//                ans[i][j] %= mod;
            }
        }
        return ans;
    }
};

struct Info {
    ll u = 0, r = 0, sy = 0, sy2 = 0, si = 0, siy = 0;
    Info operator* (const Info &info2) const {
        const Info& info1 = *this;
        Info ans{};
        ans.u = (info1.u + info2.u) % mod;
        ans.r = (info1.r + info2.r) % mod;
        ans.sy = (info1.u * info2.r + info1.sy + info2.sy) % mod;
        ans.sy2 = (info1.u * info1.u % mod * info2.r + 2ll * info1.u * info2.sy + info1.sy2 + info2.sy2) % mod;
        ans.si = (info1.r * info2.r + info1.si + info2.si) % mod;
        ans.siy = (info1.r * info2.r % mod * info1.u + info1.r * info2.sy + info1.u * info2.si +
                info1.siy + info2.siy) % mod;
        return ans;
    }
};

Info UT = {1ll, 0, 0, 0, 0, 0};
Info RT = {0, 1ll, 0, 0, 1ll, 0};

Info pow(Info x, ll y) {
    Info ans{};
    while(y) {
        if(y & 1) {
            ans = ans * x;
        }
        x = x * x;
        y >>= 1;
    }
    return ans;
}

template<typename Tag>
Tag exEuclid(ll p, ll q, ll r, ll n, const Tag &U, const Tag &R) {
    if((n * p + r) / q == 0) {
        return pow(R, n);
    }
    if(p >= q) {
        return exEuclid(p % q, q, r, n, U, pow(U, p / q) * R);
    }
    ll m = (n * p + r) / q;
    return pow(R, (q - r - 1) / p) * U *
            exEuclid(q, p, (q - r - 1) % p, m - 1, R, U) *
            pow(R, n - ((q * m - r - 1) / p));
}

int T;
using std::cin, std::cout;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin >> T;
    while(T--) {
        ll n, a, b, c;
        cin >> n >> a >> b >> c;
        auto t = pow(UT, b / c) * exEuclid(a, c, b % c, n, UT, RT);
        ll ans1 = (t.sy + b / c) % mod;
        ll ans2 = (t.sy2 + (b / c) * (b / c)) % mod;
        ll ans3 = t.siy;
        cout << ans1 << ' ' << ans2 << ' ' << ans3 << '\n';
    }
}
