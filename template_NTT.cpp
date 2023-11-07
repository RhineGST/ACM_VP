//
// Created by GST49 on 2023/10/30.
//
#include <bits/stdc++.h>
const int G = 3, Gi = 332748118, MOD = 998244353;

using ll = long long;
using std::vector, std::swap, std::cin, std::cout, std::endl;

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

template<typename T>
void NTT(T &A, vector<int> &R, int lim, int type) {
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

struct Poly : public std::vector<long long> {

    using std::vector<long long>::vector;

    bool operator<(const Poly &b) const {
        return size() > b.size();
    }

    Poly deriv() const {
        if (this->empty()) {
            return Poly();
        }
        Poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; ++i) {
            res[i] = (i + 1) * (*this)[i + 1] % MOD;
        }
        return res;
    }

    Poly integr() const {
        Poly res(this->size() + 1);
        for (int i = 0; i < this->size(); ++i) {
            res[i + 1] = (*this)[i] * power(i + 1) % MOD;
        }
        return res;
    }

    Poly shift(int k) const {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (this->size() <= -k) {
            return {};
        } else {
            return Poly(this->begin() + (-k), this->end());
        }
    }

    Poly trunc(int k) const {
        Poly f = *this;
        f.resize(k);
        return f;
    }

    Poly operator+(const Poly &b) const {
        Poly ans(std::max(size(), b.size()), 0ll);
        for(int i = 0; i < size(); i++) {
            ans[i] += (*this)[i];
        }
        for(int i = 0; i < b.size(); i++) {
            ans[i] = (ans[i] + b[i]) % MOD;
        }
        return ans;
    }

    Poly operator-(const Poly &b) const {
        Poly ans(std::max(size(), b.size()), 0ll);
        for(int i = 0; i < size(); i++) {
            ans[i] += (*this)[i];
        }
        for(int i = 0; i < b.size(); i++) {
            ans[i] = (ans[i] - b[i]) % MOD;
        }
        return ans;
    }

    Poly operator*(Poly B) const {
        Poly A = *this;
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

    Poly operator* (ll v) const {
        auto ans = *this;
        for(auto &x : ans) {
            x = x * v % MOD;
        }
        return ans;
    }

    Poly inv(int m) const {
        Poly x{power((*this)[0], MOD - 2)}, poly_two{2ll};
        int k = 1;
        while(k < m) {
            k <<= 1;
            x = x * (poly_two - trunc(k) * x);
            x.resize(k);
        }
        x.resize(m);
        return x;
    }

    Poly log(int m) const {
        auto ans = (deriv() * inv(m)).integr();
        ans.resize(m);
        return ans;
    }

    Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while(k < m) {
            k <<= 1;
            x = x * (Poly{1} - x.log(k) + trunc(m));
            x.resize(k);
        }
        x.resize(m);
        return x;
    }

    Poly pow(int k, int m) const {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() || 1LL * i * k >= m) {
            return Poly(m);
        }
        auto v = (*this)[i];
        auto f = shift(-i) * power(v);
        return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
    }
};

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

int main() {

}