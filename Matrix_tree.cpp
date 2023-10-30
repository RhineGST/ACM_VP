#include<bits/stdc++.h>
#define maxn 305

typedef long long ll;
const ll mod = 1e9 + 7;

ll pow(ll x, ll y){
    ll ans = 1;
    while(y){
        if(y & 1) ans = ans * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}

ll num(ll x, ll y){
    return x * pow(y, mod - 2) % mod;
}

template<typename T>
struct Matrix{
    int n, m;
    T val[maxn][maxn];
    Matrix(int n, int m) : n(n), m(m){
        memset(val, 0, sizeof(val));
    }

    T* operator [](int x){
        return val[x];
    }

    void swap(T &x, T &y){
        T temp = x;
        x = y;
        y = temp;
    }

    void swapLine(int x, int y){
        for(int i = 0; i < m; i++) swap(val[x][i], val[y][i]);
    }


    T det(void){
        T ans = 1;
        if(n != m) return 0;
        for(int i = 0; i < n; i++){
            int maxArg = i;
            for(int k = i + 1; k < n; k++)
                maxArg = val[maxArg][i] > val[k][i] ? maxArg : k;
            if(maxArg != i) swapLine(maxArg, i), ans = -ans;
            if(val[i][i] == 0) return 0;
            for(int j = i + 1; j < n; j++){
                if(val[j][i] == 0) continue;
                T div = num(val[j][i], val[i][i]);
                for(int k = i; k < m; k++)
                    val[j][k] = (val[j][k] + mod - val[i][k] * div % mod) % mod;
            }
        }
        ans = ans > 0 ? ans : (mod - 1);
        for(int i = 0; i < n; i++)
            ans = ans * val[i][i] % mod;
        return ans;
    }
};

int n, m;

int main(void){
    int t;
    scanf("%d%d%d", &n, &m, &t);
    Matrix<ll> ans(n - 1, n - 1);
    for(int x, y, z, i = 1; i <= m; i++){
        scanf("%d%d%d", &x, &y, &z);
        x--, y--;
        if(t == 0){
            ans[x][y] = (ans[x][y] + mod - z) % mod;
            ans[y][x] = (ans[y][x] + mod - z) % mod;
            ans[x][x] = (ans[x][x] + z) % mod;
            ans[y][y] = (ans[y][y] + z) % mod;
        }
        else{
            ans[x][y] = (ans[x][y] + mod - z) % mod;
            ans[y][y] = (ans[y][y] + z) % mod;
        }
    }
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            ans[i - 1][j - 1] = ans[i][j];
        }
    }
    printf("%lld\n", ans.det());
}