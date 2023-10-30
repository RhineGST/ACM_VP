//
// Created by GST49 on 2023/10/28.
//
#include "bits/stdc++.h"
using ll = long long;
const int maxn  = 1e5 + 6;

ll mod;

ll F[maxn];

template<typename T>
T pow(T x, ll y) {
    T ans = 1ll;
    while(y) {
        if(y & 1) {
            ans = ans * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}

ll num(ll x, ll y) {
    return x * pow(y, mod - 2) % mod;
}

ll A(ll n, ll m) {
    return num(F[n], F[n - m]);
}

ll C(ll n, ll m) {
    if(m > n) {
        return 0;
    }
    return num(A(n, m), F[m]);
}

long long Lucas(long long n, long long m, long long p) {
    if (m == 0) return 1;
    else return (C(n % p, m % p) * Lucas(n / p, m / p, p)) % p;
}

int T;
using std::cin, std::cout;

int main() {
    std::cin >> T;
    F[0] = 1ll;
    while(T--) {
        ll n, m;
        cin >> n >> m >> mod;
        for(int i = 1; i < mod; i++) {
            F[i] = F[i - 1] * i % mod;
        }
        cout << Lucas(n + m, n, mod) << std::endl;
    }
}