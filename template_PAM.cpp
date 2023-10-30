#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;

struct PAM {
    struct Node {
        int son[26], len, fail;
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

    void insert(char ch) {
        str[++str_tot] = ch;
        int cur = get_fail(last, str_tot);
        int branch = ch - 'a';
        if(!node[cur].son[branch]) {
            int node_t = new_node();
            node[node_t].len = node[cur].len + 2;
            node[node_t].fail = node[get_fail(node[cur].fail, str_tot)].son[branch];
            node[cur].son[branch] = node_t;
        }
        last = node[cur].son[branch];
    }
} pam;