#include<bits/stdc++.h>

const int maxn = 1e4 + 5;

struct Node {
	int link, len;
	long long size;
	int son[27];
	
	Node() {
		link = len = 0;
		memset(son, 0, sizeof(son));
	}
};

struct SAM {
	int root, tot, last;
	Node node[maxn << 1];
	
	SAM() {
		tot = 0;
		root = newNode();
		last = root;
	}
	
	int newNode() {
		node[++tot] = {};
		return tot;
	}
	
	void insert(char ch) {
		auto cur = newNode();
		int branch = ch - 'a';
		node[cur].size = 1;
		node[cur].len = node[last].len + 1;
		while(last != 0 && (node[last].son[branch] == 0)) {
			node[last].son[branch] = cur;
			last = node[last].link;
		}
		if(last == 0) {
			node[cur].link = root;
		}
		else {
			int q = node[last].son[branch];
			if(node[q].len == node[last].len + 1) {
				node[cur].link = q;
			}
			else {
				int clone = newNode();
				node[clone] = node[q];
				node[clone].len = node[last].len + 1;
				node[clone].size = 0;
				while(last != 0 && node[last].son[branch] == q) {
					node[last].son[branch] = clone;
					last = node[last].link;
				}
				node[q].link = clone;
				node[cur].link = clone;
			}
		}
		last = cur;
	}
	
	void getSize() {
		std::vector<int> cnt(tot + 1, 0);
		for(int i = root + 1; i <= tot; i++) {
			cnt[node[i].link]++;
		}
		
		std::queue<int> q;
		
		for(int i = root + 1; i <= tot; i++) {
			if(cnt[i] == 0) {
				q.push(i);
			}
		}
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			int y = node[x].link;
			node[y].size += node[x].size;
			if(--cnt[y] == 0) {
				q.push(y);
			}
		}
	}
	
	void clear() {
		tot = 0;
		root = newNode();
		last = root;
	}
} sam;
