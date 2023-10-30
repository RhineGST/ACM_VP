#include <bits/stdc++.h>

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;

using std::vector;
using std::string;

using ll = long long;

const ll mod = 1e9 + 7;

struct PAM {
    struct Node {
        int son[26], len, fail, diff, top;
    };

    int node_tot, str_tot, last;
    Node node[maxn << 1];
    char str[maxn]{};

    PAM() {
        clear();
    }

    void clear() {
        node_tot = -1;
        str_tot = 0;
        last = 0;
        str[0] = '$';
        node[new_node()].len = 0;
        node[new_node()].len = -1;
        node[0].fail = 1;
    }

    int new_node() {
        node[++node_tot] = {};
        return node_tot;
    }

    int get_fail(int x, int index) {
        while (str[index - node[x].len - 1] != str[index]) {
            x = node[x].fail;
        }
        return x;
    }

    void update(int x) {
        node[x].diff = node[x].len - node[node[x].fail].len;
        if(node[x].diff == node[node[x].fail].diff) {
            node[x].top = node[node[x].fail].top;
        }
        else {
            node[x].top = node[x].fail;
        }
    }

    void insert(char ch) {
        str[++str_tot] = ch;
        int cur = get_fail(last, str_tot);
        int branch = ch - 'a';
        if(!node[cur].son[branch]) {
            int node_t = new_node();
            node[node_t].len = node[cur].len + 2;
            node[node_t].fail = node[get_fail(node[cur].fail, str_tot)].son[branch];
            node[cur].son[branch] = node_t;
            update(node_t);
        }
        last = node[cur].son[branch];
    }

    void calc(int index, long long *g, long long *f) {
        for(int p = last; p > 1; p = node[p].top) {
            g[p] = f[index - node[node[p].top].len - node[p].diff];
            if(node[p].top != node[p].fail) {
                g[p] = (g[p] + g[node[p].fail]) % mod;
            }
            f[index] = (f[index] + g[p]) % mod;
        }
        if(index & 1) {
            f[index] = 0;
        }
    }
} pam;

int n, tot;
char str[maxn], input[maxn];
ll f[maxn], g[maxn];

//询问一个字符串可以被划分为分段回文的情况数，类似a|ab|ab|a，讲字符串折叠后变为求一个字符串偶数回文的情况书

int main() {
    std::cin >> input;
    n = (int)strlen(input);
    for(int i = 0; i < (n >> 1); i++) {
        str[++tot] = input[i];
        str[++tot] = input[n - i - 1];
    }
    f[0] = 1;
    str[++tot] = '\0';
    for(int i = 1; i <= n; i++) {
        pam.insert(str[i]);
        pam.calc(i, g, f);
    }
    std::cout << f[n];
}