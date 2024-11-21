#include<bits/stdc++.h>

struct Tag {
    long long x;
    void operator+=(const Tag &o) {
        x += o.x;
    }
};

struct Info {
    long long x;
    int len;

    Info() : x(0), len(0) {};

    Info(int v) {
        x = v;
        len = 1;
    }

    void operator+=(const Info &o) {
        x += o.x;
        len += o.len;
    }

    void operator+=(const Tag &o) {
        x += len * o.x;
    }
};

struct SegTree {
    std::vector<Info> info;
    std::vector<Tag> tag;
    int n;
    explicit SegTree(int n_) : n(n_), info(n_ * 4 + 1), tag(n_ * 4 + 1) {}

    template<typename Array>
    void init(int x, int l, int r, Array &data) {
        if(l == r) {
            info[x] = Info(data[l]);
        } else {
            int mid = (l + r) / 2;
            init(x * 2, l, mid, data);
            init(x * 2 + 1, mid + 1, r, data);
            pull_up(x, l == r);
        }
    }

    template<typename Array>
    void init(Array &data) {
        init(1, 1, n, data);
    }

    void apply(int x, const Tag &v) {
        info[x] += v;
        tag[x] += v;
    }

    void push_down(int x, bool leaf) {
        if(!leaf) {
            apply(x * 2, tag[x]);
            apply(x * 2 + 1, tag[x]);
        }
        tag[x] = {};
    }

    void pull_up(int x, bool leaf) {
        push_down(x, leaf);
        if(!leaf) {
            info[x] = info[x * 2];
            info[x] += info[x * 2 + 1];
        }
    }

    void update(int x, int l, int r, int lq, int rq, const Tag &v) {
        push_down(x, l == r);
        if(lq <= l && rq >= r) {
            apply(x, v);
        } else if(lq > r || rq < l) {
            return;
        } else {
            int mid = (l + r) / 2;
            update(x * 2, l, mid, lq, rq, v);
            update(x * 2 + 1, mid + 1, r, lq, rq, v);
            pull_up(x, l == r);
        }
    }

    void update(int lq, int rq, const Tag &v) {
        update(1, 1, n, lq, rq, v);
    }

    void modify(int x, int l, int r, int pos, const Info &v) {
        push_down(x, l == r);
        if(l == r) {
            info[x] = v;
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid) {
            modify(x * 2, l, mid, pos, v);
        } else {
            modify(x * 2 + 1, mid + 1, r, pos, v);
        }
        pull_up(x, l == r);
    }

    void modify(int pos, const Info &v) {
        modify(1, 1, n, pos, v);
    }

    Info ask(int x, int l, int r, int lq, int rq) {
        push_down(x, l == r);
        if(lq <= l && rq >= r) {
            return info[x];
        } else if(lq > r || rq < l) {
            return Info{};
        } else {
            int mid = (l + r) / 2;
            auto ans = ask(x * 2, l, mid, lq, rq);
            ans += ask(x * 2 + 1, mid + 1, r, lq, rq);
            return ans;
        }
    }

    Info ask(int lq, int rq) {
        return ask(1, 1, n, lq, rq);
    }

    template<typename CheckFun>
    int find(int x, int l, int r, int lq, int rq, Info &sum, CheckFun &&check) {
        push_down(x, l == r);
        if (lq <= l && rq >= r) {
            auto sum_t = sum;
            sum_t += info[x];
            if (!check(sum_t)) {
                sum = sum_t;
                return -1;
            }
            if(l == r) {
                return l;
            }
        } else if (lq > r || rq < l) {
            return -1;
        }
        int mid = (l + r) / 2;
        int ans = find(x * 2, l, mid, lq, rq, sum, check);
        return (ans != -1) ? ans : find(x * 2 + 1, mid + 1, r, lq, rq, sum, check);
    }

    template<typename CheckFun>
    int find(int lq, int rq, CheckFun &&check) {
        Info sum = {};
        return find(1, 1, n, lq, rq, sum, check);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    SegTree seg(n);
    seg.init(a);
    while(m--) {
        int opt;
        std::cin >> opt;
        if(opt == 1) {
            int x, y, k;
            std::cin >> x >> y >> k;
            seg.update(x, y, Tag{k});
        } else {
            int x, y;
            std::cin >> x >> y;
            std::cout << seg.ask(x, y).x << '\n';
        }
    }
}