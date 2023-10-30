#include <bits/stdc++.h>

using std::vector;
using std::string;

vector<int> getFail(const string &str) {
    vector<int> fail(str.size(), 0);
    fail[0] = -1;
    for(int i = 1; i < str.size(); i++) {
        int now = fail[i - 1];
        while(now >= -1 && str[now + 1] != str[i]) {
            now = now > -1 ? fail[now] : -2;
        }
        fail[i] = now + 1;
    }
    return fail;
}

void kmp(const string &str, const vector<int> &fail, const string &str_t) {
    int now = -1;
    for(int i = 0; i < str_t.size(); i++) {
        while(now >= -1 && str[now + 1] != str_t[i]) {
            now = now > -1 ? fail[now] : -2;
        }
        now += 1;
        if(now == str.size() - 1) {
            std::cout << i + 2 - str.size() << '\n';
            now = fail[now];
        }
    }
}

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    auto fail = getFail(s2);
    kmp(s2, fail, s1);
    for(auto num : fail) {
        std::cout << num + 1 << ' ';
    }
}