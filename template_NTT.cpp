//
// Created by GST49 on 2023/10/30.
//
#include <bits/stdc++.h>
const int G = 3, Gi = 332748118, MOD = 998244353;
const int G = 15311432, Gi = 469870224, MOD = 998244353;

using ll = long long;
using std::vector, std::swap, std::cin, std::cout, std::endl;

struct Poly : public std::vector<long long> {

    using std::vector<long long>::vector;

    bool operator<(const Poly &b) const {
        return size() > b.size();
    }
};

std::priority_queue<Poly> q;

ll power(ll a, ll b = MOD - 2, ll p = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void NTT(Poly &A, vector<int> &R, int lim, int type) {
    for (int i = 0; i < lim; i++) {
        if (i < R[i]) {
            swap(A[i], A[R[i]]);
        }
    }
    for (int mid = 1; mid < lim; mid <<= 1) {
        ll wn = power(type == 1 ? G : Gi, (MOD - 1) / (mid << 1));
        for (int len = mid << 1, pos = 0; pos < lim; pos += len) {
            long long w = 1;
            for (int k = 0; k < mid; ++k, w = w * wn % MOD) {
                long long x = A[pos + k];
                long long y = w * A[pos + mid + k] % MOD;
                A[pos + k] = (x + y) % MOD;
                A[pos + mid + k] = (x - y + MOD) % MOD;
            }
        }
    }
    if (type == -1) {
        long long inv = power(lim, MOD - 2);
        for (int i = 0; i < lim; i++) {
            A[i] = (A[i] * inv % MOD + MOD) % MOD;
        }
    }
}

Poly operator*(Poly A, Poly B) {
    int lim = 1, lim_bit = 0;
    auto sz = A.size() + B.size() - 1;
    while (lim <= A.size() + B.size()) {
        lim <<= 1, lim_bit++;
    }
    A.resize(lim);
    B.resize(lim);
    vector<int> R(lim, 0);
    for (int i = 1; i < lim; i++) {
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (lim_bit - 1));
    }
    NTT(A, R, lim, 1);
    NTT(B, R, lim, 1);
    Poly res(lim, 0);
    for (int i = 0; i < lim; i++) {
        res[i] = A[i] * B[i] % MOD;
    }
    NTT(res, R, lim, -1);
    res.resize(sz);
    return res;
}

// 求原根
template<int P>
constexpr ll findPrimitiveRoot() {
    ll i = 2;
    int k = __builtin_ctz(P - 1);
    while (true) {
        if (power(i, (P - 1) / 2, P) != 1) {
            break;
        }
        i += 1;
    }
    return power(i, (P - 1) >> k, P);
}