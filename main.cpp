#include "bits/stdc++.h"

const int p_list[] = {2, 3, 5, 7, 11, 13, 17, 19};

using ll = long long;
ll dp[1 << 8][500], now[1 << 8][500], sum[1 << 8];
ll ans, p;

struct Node {
    int s, x;
};

std::vector<Node> bag;

using std::cin, std::cout, std::endl;

int main() {
    int n;
    cin >> n >> p;
    for(int i = 2; i <= n; i++) {
        int S = 0, x = i;
        for(int k = 0; k < 8; k++) {
            if(x % p_list[k] != 0) {
                continue;
            }
            S |= (1 << k);
            while(x % p_list[k] == 0) {
                x /= p_list[k];
            }
        }
        bag.push_back({S, x});
    }
    dp[0][1] = 1;
    for(auto [s_i, x] : bag) {
        for(int s = 0; s < (1 << 8); s++) {
            if(x == 1) {
                now[s | s_i][1] = (now[s | s_i][1] + dp[s][1]) % p;
            }
            else {
                now[s | s_i][x] = (now[s | s_i][x] + dp[s][x] + dp[s][1]) % p;
            }
        }
        for(int s = 0; s < (1 << 8); s++) {
            for(int i = 1; i <= n; i++) {
                dp[s][i] = (dp[s][i] + now[s][i]) % p;
                now[s][i] = 0;
            }
        }
    }
    for(int s = 0; s < (1 << 8); s++) {
        for(int i = 1; i <= n; i++) {
            sum[s] = (sum[s] + dp[s][i]) % p;
        }
    }
    for(int s = 0; s < (1 << 8); s++) {
        int s_t = (((1 << 8) - 1) ^ s);
        for(int s_son = s_t; s_son; s_son = (s_son - 1) & s_t) {
            ans = (ans + dp[s][1] * sum[s_son]) % p;
        }
        ans = (ans + dp[s][1] * sum[0]) % p;
        for(int i = 2; i <= n; i++) {
            for(int s_son = s_t; s_son; s_son = (s_son - 1) & s_t) {
                ans = (ans + dp[s][i] * (sum[s_son] - dp[s_son][i] + p)) % p;
            }
            ans = (ans + dp[s][i] * (sum[0] - dp[0][i] + p)) % p;
        }
    }
    cout << ans << endl;
}