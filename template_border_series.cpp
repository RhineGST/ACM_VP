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

int gcd(int a, int b, const vector<int> &fail) {
    a = fail[a], b = fail[b];
    while(a != b && (a != -1) && (b != -1)) {
        if(a < b) {
            std::swap(a, b);
        }
        if(fail[a] + 1 > (a + 1) / 2) {
            int d = a - fail[a];
            if((a + 1) % d == (b + 1) % d) {
                return b + 1;
            }
            else {
                a = (a + 1) % d + d - 1;
            }
        }
        else {
            a = fail[a];
        }
    }
    return std::min(a, b) + 1;
}

int main() {
    string s;
    std::cin >> s;
    auto fail = getFail(s);
    int n;
    std::cin >> n;
    while(n--) {
        int x, y;
        std::cin >> x >> y;
        std::cout << gcd(x - 1, y - 1, fail) << '\n';
    }
    return 0;
}