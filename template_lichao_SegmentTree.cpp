#include<bits/stdc++.h>
#define maxn 100005

template <typename Line>
struct LCTree{
    //一个类Line，和一个比较函数cmp，cmp(x, y, t)表示在t的时候，Line x是否优于Line y
    int root, n, tot;
    std::vector<int> ls, rs;
    std::vector<Line> line;
    std::function<bool(Line x, Line y, int t)> cmp = [](Line x, Line y, int t) -> bool{return true;};

    LCTree(void){

    }

    LCTree(int n, std::function<bool(Line x, Line y, int t)> cmp){
        this -> n = n;
        this -> tot = 0;
        this -> cmp = cmp;
        ls.resize(n << 1);
        rs.resize(n << 1);
        line.resize(n << 1);
        clear();
    }

    int newNode(Line v){
        line[++tot] = v;
        ls[tot] = rs[tot] = 0;
        return tot;
    }

    int insert(Line t, int now, int l, int r)
    {
        if(r < t.k) return 0;
        if(!now) return newNode(t);
        int mid = (l + r) >> 1;
        bool lc1 = cmp(t, line[now], l), rc1 = cmp(t, line[now], r);
        bool lc2 = cmp(line[now], t, l), rc2 = cmp(line[now], t, r);
        if(!lc1 && !rc1){return now;}
        if(!lc2 && !rc2){line[now] = t; return now;}
        if(lc1){
            if(cmp(t, line[now], mid)) rs[now] = insert(line[now], rs[now], mid + 1, r), line[now] = t;
            else ls[now]=insert(t, ls[now], l, mid);
        }
        else if(rc1){
            if(cmp(t, line[now], mid + 1)) ls[now] = insert(line[now], ls[now], l, mid), line[now] = t;
            else rs[now] = insert(t, rs[now], mid + 1, r);
        }
        return now;
    }

    void insert(Line t){
        root = insert(t, root, 1, n);
    }

    Line better(Line x, Line y, int t){
        return cmp(x, y, t) ? x : y;
    }

    Line ask(int x, int now, int l, int r){
        if(!now) return Line();
        int mid = (l + r) >> 1;
        if(x <= mid) return ls[now] ? better(ask(x, ls[now], l, mid), line[now], x) : line[now];
        else return rs[now] ? better(ask(x, rs[now], mid + 1, r), line[now], x) : line[now];
    }

    Line ask(int x){
        return ask(x, root, 1, n);
    }

    void clear(void){
        root = 0, tot = 0;
    }
};

int c[maxn], n, sum[maxn], mc, id[maxn];
unsigned long long dp[maxn];

unsigned long long pow(unsigned long long x){
    return x * x;
}

struct Line{
    int k, col;
    unsigned long long b;
    Line(void){
        k = col = b = 0;
    }
    Line(int k, unsigned long long b, int col){
        this -> k = k;
        this -> b = b;
        this -> col = col;
    }
    unsigned long long calc(int x){
        return b + pow(x + 1llu - k) * col;
    }
};

auto cmp = [](Line x, Line y, int t) -> bool{
    if(x.k > t || y.k > t) return x.calc(std::max(x.k, y.k)) > y.calc(std::max(x.k, y.k));
    return x.calc(t) > y.calc(t);
};

LCTree<Line> tree[maxn];

int main(void){
// 	freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", c + i);
        id[i] = ++sum[c[i]];
        mc = std::max(mc, c[i]);
    }
    for(int i = 1; i <= mc; i++){
        if(sum[i] == 0) continue;
        tree[i] = LCTree<Line>(sum[i], cmp);
    }
    for(int i = 1; i <= n; i++){
        tree[c[i]].insert(Line(id[i], dp[i - 1], c[i]));
        dp[i] = tree[c[i]].ask(id[i]).calc(id[i]);
    }
    printf("%llu\n", dp[n]);
}