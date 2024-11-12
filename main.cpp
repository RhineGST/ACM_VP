#include <bits/stdc++.h>

const int N = 4;

struct Node {
    std::deque<int> q;
    bool fl = true;

    void move(int x) {
        if(x <= 0) {
            return;
        }
        int sub_num = 0;
        fl ^= (x & 1);
        while(!q.empty() && x > 0) {
            int &v = q.back();
            sub_num += std::min(v, x);
            if(x >= v) {
                x -= v;
                q.pop_back();
            } else {
                v -= x;
                x = 0;
            }
        }
        if(q.empty()) {
            q.push_front(sub_num);
        } else {
            q.front() += sub_num;
        }
    }

    void add(int x) {
        if(q.empty()) {
            q.push_front(x);
        } else if ((!(x & 1)) && !fl) {
            q.push_front(x);
        } else if((x & 1) && fl) {
            q.front()--;
            if(q.front() == 0) {
                q.pop_front();
            }
            q.push_front(x + 1);
        } else {
            q.front() += x;
        }
        fl = true;
    }

    bool check() {
        int fl_t = fl;
        for(auto &v : q) {
            fl_t ^= (!(v & 1));
        }
        return !fl_t;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::map<int, int> a;
    for(int x, i = 1; i <= n; i++) {
        std::cin >> x;
        a[-x]++;
    }
    Node node;
    int last = -1;
    for(auto &[x, v] : a) {
        if(last != -1) {
            node.move(last + x);
        }
        last = -x;
        node.add(v);
    }
    node.move(last - 1);
    if(node.check()) {
        std::cout << "First" << std::endl;
    } else {
        std::cout << "Second" << std::endl;
    }
}