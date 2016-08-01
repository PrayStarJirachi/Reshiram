#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>

const int MAXN = 400001;
const int MAXM = 400001;

struct Edge{
	int node, next;
}e[MAXM];

int M, n, q, t, tot, h[MAXN], tree[MAXN * 4], d[MAXN], f[MAXN], w[MAXN];
std::pair<int, int> o[MAXN];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void dfs(int x) {
	w[o[x].first = ++tot] = x;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x]) continue;
		d[e[i].node] = d[x] + 1;
		dfs(e[i].node);
	}
	o[x].second = tot;
}

void buildtree(int n, int l, int r) {
	tree[n] = 1;
	if (l == r) return;
	buildtree(n << 1, l, l + r >> 1);
	buildtree(n << 1 ^ 1, (l + r >> 1) + 1, r);
}

int query(int n, int l, int r, int x) {
	if (l == r) return tree[n];
	if (x <= (l + r >> 1)) {
		return std::max(tree[n], query(n << 1, l, l + r >> 1, x));
	} else {
		return std::max(tree[n], query(n << 1 ^ 1, (l + r >> 1) + 1, r, x));
	}
}

void cover(int n, int l, int r, int x, int y, int d) {
	if (r < x || l > y) return;
	if (x <= l && r <= y) {
		tree[n] = std::max(tree[n], d);
		return;
	}
	cover(n << 1, l, l + r >> 1, x, y, d);
	cover(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, d);
}

int main() {
	freopen("F.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	while (true) {
		std::cin >> n >> q;
		if (n == 0 && q == 0) break;
		tot = 0;
		std::fill(h + 1, h + n + 1, t = 0);
		for (int i = 2; i <= n; i++) {
			std::cin >> f[i];
			addEdge(i, f[i]);
		}
		dfs(1);
		buildtree(1, 1, n);
		long long answer = 0;
		for (int i = 1; i <= q; i++) {
			char op[20];
			int x;
			std::cin >> op >> x;
			if (op[0] == 'M') {
				cover(1, 1, n, o[x].first, o[x].second, o[x].first);
			} else {
				answer += w[query(1, 1, n, o[x].first)];
			}
		}
		std::cout << answer << std::endl;
	}
	return 0;
}
