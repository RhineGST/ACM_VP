#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
struct Hash {
    static const long long P1 = 993244853, BASE1 = 131;
    static const long long P2 = 1000000009, BASE2 = 13331;
    static long long B1[maxn], B2[maxn];

    static void init(int max_size) {
        B1[0] = 1ll, B2[0] = 1ll;
        for(int i = 1; i <= max_size; i++) {
            B1[i] = B1[i - 1] * BASE1 % P1;
            B2[i] = B2[i - 1] * BASE2 % P2;
        }
    }

    long long a1, a2;
    bool operator==(const Hash &b) const {
        return a1 == b.a1 && a2 == b.a2;
    }
    bool operator<(const Hash &b) const {
        return a1 == b.a1 ? a2 < b.a2 : a1 < b.a1;
    }
    Hash operator+(const int b) const {
        return { (a1 * BASE1 + b) % P1, (a2 * BASE2 + b) % P2 };
    }
    Hash operator<<(const int b) const {
        return { a1 * B1[b] % P1, a2 * B2[b] % P2 };
    }
    Hash operator-(const Hash &b) const {
        return { (a1 - b.a1 + P1) % P1, (a2 - b.a2 + P2) % P2 };
    }
} h[maxn];

long long Hash::B1[maxn], Hash::B2[maxn];

Hash split(int l, int r) {
    return h[r] - (h[l - 1] << (r - l + 1));
}