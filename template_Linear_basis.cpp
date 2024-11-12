#include<bits/stdc++.h>

const int N = 55;

template<int S>
struct Hamel{
    std::bitset<S> val[S];
    Hamel(void) {}

    bool insert(std::bitset<S> x) {
        for(int i = S - 1; i >= 0; i--){
            if(x[i]){
                if(val[i] == 0){
                    val[i] = x;
                    return true;
                }
                else{
                    x = x ^ val[i];
                    if(x == 0) return false;
                }
            }
        }
        return false;
    }
    std::bitset<S> getMax(std::bitset<S> ans){
        for(int i = S - 1; i >= 0; i--){
            if(ans[i]) continue;
            ans = ans ^ val[i];
        }
        return ans;
    }
    std::bitset<S> getMin(std::bitset<S> ans){
        for(int i = S - 1; i >= 0; i--){
            if(ans[i]){
                ans = ans ^ val[i];
            }
        }
        return ans;
    }
};

/**
typedef long long ll;
const ll mod = 998244353;

ll pow2[200005];

template<int S>
struct Hamel{
    std::bitset<S> val[S];
    ll cnt[S];
    Hamel(void) {
        memset(cnt, 0, sizeof(cnt));
    }

    bool insert(std::bitset<S> x) {
        for(int i = S - 1; i >= 0; i--){
            if(x[i]){
                if(val[i] == 0){
                    val[i] = x;
                    cnt[i] = 1;
                    return true;
                }
                else{
                    x = x ^ val[i];
                    if(x == 0){
                        cnt[i] += 1;
                        return false;
                    }
                }
            }
        }
        return false;
    }

    ll query(std::bitset<S> x) {
        ll ans = 1ll;
        for(int i = S - 1; i >= 0; i--){
            if(x[i]){
                if(val[i] == 0){
                    return 0ll;
                }
                else{
                    x = x ^ val[i];
                    ans = ans * (pow2[cnt[i] - 1]) % mod;
                }
            }
            else{
                if(cnt[i] != 0)
                    ans = ans * (pow2[cnt[i] - 1]) % mod;
            }
        }
        return ans;
    }
};
 **/

int n;

int main(){
    scanf("%d", &n);
    Hamel<51> c;
    for(int i = 1; i <= n; i++){
        unsigned long long x;
        scanf("%llu", &x);
        c.insert(std::bitset<51>(x));
    }
    printf("%llu\n", c.getMax(0).to_ullong());
}