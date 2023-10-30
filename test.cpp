//
// Created by GST49 on 2023/10/25.
//
#include<bits/stdc++.h>
std::vector<int> factors[1000005];
int main() {
    for(int i = 2; i <= 1e6; i++) {
        for(int j = 1; i * j <= 1e6; j++) {
            factors[i * j].emplace_back(i);
        }
    }
    return 0;
}