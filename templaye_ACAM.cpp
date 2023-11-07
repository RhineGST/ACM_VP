#include <bits/stdc++.h>

const int maxn = 1e6 + 6;

struct Node {
    int son[26], fail;
    std::vector<int> valid_num;
};

struct Trie {
    Node node[maxn];
    int root, tot, size;

    bool vis[maxn];
    int fail_num[maxn], fail_val[maxn];

    int new_node() {
        tot++;
        node[tot] = {};
        return tot;
    }

    void insert(const std::string& str, int id, int d, int &x) {
        if(!x) {
            x = new_node();
        }
        if(d == str.length()) {
            node[x].valid_num.push_back(id);
            return;
        }
        else {
            insert(str, id, d + 1, node[x].son[str[d] - 'a']);
        }
    }

    void insert(const std::string& str, int id) {
        ++size;
        insert(str, id, 0, root);
    }

    void getFail() {
        std::queue<int> q;
        for(int i = 0; i < 26; i++) {
            if(node[root].son[i]) {
                node[node[root].son[i]].fail = root;
                q.push(node[root].son[i]);
            }
            else {
                node[root].son[i] = root;
            }
        }
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(int i = 0; i < 26; i++) {
                if(node[x].son[i]) {
                    node[node[x].son[i]].fail = node[node[x].fail].son[i];
                    q.push(node[x].son[i]);
                }
                else {
                    node[x].son[i] = node[node[x].fail].son[i];
                }
            }
        }
    }

    std::vector<int> match(const std::string& str) {
        int now = root;
        auto ans_num = std::vector<int>(size + 1, 0);
        for(int i = 1; i <= tot; i++) {
            if(node[i].fail) {
                fail_num[node[i].fail]++;
            }
        }
        for(const auto &ch : str) {
            now = node[now].son[ch - 'a'];
            fail_val[now]++;
        }
        std::queue<int> q;
        for(int i = 1; i <= tot; i++) {
            if(fail_num[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            if(x == root) {
                break;
            }
            for(const auto &id : node[x].valid_num) {
                ans_num[id] += fail_val[x];
            }
            fail_val[node[x].fail] += fail_val[x];
            fail_num[node[x].fail] -= 1;
            if(fail_num[node[x].fail] == 0) {
                q.push(node[x].fail);
            }
        }
        return ans_num;
    }

    void clear() {
        root = 0;
        tot = 0;
        size = 0;
    }
} trie;

int n;
std::string form_str, input[maxn];

//输入一个模板串，以及很多询问，询问你每个询问在模板串上出现了多少次

int main() {
    std::cin >> n;
    if(n == 0) {
        return 0;
    }
    trie.clear();
    for(int i = 1; i <= n; i++) {
        std::cin >> input[i];
        trie.insert(input[i], i);
    }
    trie.getFail();
    std::cin >> form_str;
    auto ans_num = trie.match(form_str);
    for(int i = 1; i <= n; i++) {
        std::cout << ans_num[i] << std::endl;
    }
}