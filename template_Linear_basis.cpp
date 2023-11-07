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