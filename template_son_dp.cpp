#include "bits/stdc++.h"
const long long INF = 0x7ffffffffffffll;
using ll = long long;
const ll MOD = 1e9 + 7;

template<typename T>
void son_dp(std::vector<T> &dp, int limit) {
    limit = 1 << limit;
    for(int k = limit >> 1; k > 0; k >>= 1) {
        for(int i = 0; i < limit; i++) {
            if(i & k) {
                dp[i] += dp[i ^ k];
            }
        }
    }
} //输入初始数组dp和他的长度(2 ^ limit)，对它的每一个子集求和

using std::cin, std::cout, std::endl, std::vector;
int sz[1 << 21];
ll pow2[1 << 21];

int main() { //求解从n个物品中，选出全集的方案数，使用容斥+son_dp
    int n, N;
    cin >> n >> N;
    pow2[0] = 1ll;
    for(int i = 1; i < (1 << N); i++) {
        sz[i] = sz[i - (i & -i)] + 1;
    }
    std::vector<int> dp(1 << N, 0);
    for(int x, s, i = 1; i <= n; i++) {
        cin >> x;
        s = 0;
        for(int t, j = 0; j < x; j++) {
            cin >> t;
            s |= (1 << (t - 1));
        }
        dp[s]++;
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
    son_dp(dp, N);
    ll ans = 0;
    for(int i = 0; i < (1 << N); i++) {
        if((sz[i] & 1) ^ (sz[(1 << N) - 1] & 1)) {
            ans = (ans - pow2[dp[i]] + MOD) % MOD;
        }
        else {
            ans = (ans + pow2[dp[i]]) % MOD;
        }
    }
    cout << ans << endl;
}