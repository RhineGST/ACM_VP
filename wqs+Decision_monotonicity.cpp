#include<bits/stdc++.h>

#define maxn 500005

struct Node {
    int x, k;

    Node(int u = 0, int v = 0) {
        x = u, k = v;
    }
} q[maxn];

long long dp[maxn], sum[maxn];
int s[maxn], d[maxn];
int n, m, hd, tl;

long long calc(int l, int r) {
    int mid = (l + r + 1) >> 1;
    return (sum[r] - sum[mid]) - d[mid] * 1ll * (r - mid) + d[mid] * 1ll * (mid - l) - (sum[mid] - sum[l]);
}

int find(int i, int j) {
    int l = j, r = n + 1;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (dp[i] + calc(i, mid) < dp[j] + calc(j, mid)) l = mid;
        else r = mid;
    }
    return r;
}

bool check(int mid) {
    hd = 1, tl = 0;
    q[++tl] = Node(0, n + 1);
    for (int i = 1; i <= n; i++) {
        while (hd < tl && q[hd].k <= i) hd++;
        dp[i] = dp[q[hd].x] + calc(q[hd].x, i) + mid;
        s[i] = s[q[hd].x] + 1;
        while (hd < tl && find(q[tl].x, i) <= q[tl - 1].k) tl--;
        q[tl].k = find(q[tl].x, i);
        q[++tl] = Node(i, n + 1);
    }
    return s[n] >= m;
}

//wqs二分只需要计算sz最小的即可，不需要保存上下
//题目为给你一些村庄的位置，你可以选择在m个村庄建邮局，让每个村庄距离最短邮局的距离和最小

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", d + i);
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + d[i];
    long long l = 0, r = 5e11;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    check(l);
    printf("%lld\n", dp[n] - m * l);
}