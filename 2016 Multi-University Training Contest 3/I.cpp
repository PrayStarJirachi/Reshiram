#include <cstdio>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;

struct Edge{
	int node, next;
}e[MAXM];

int n, q, cnt, size, t, h[MAXN], f[MAXN][21], depth[MAXN];
unsigned int bit[MAXN], p[MAXN], w[MAXN], s[MAXN], answer[MAXN], val[MAXN], p[MAXN], deg[MAXN], d[MAXN];
std::pair<int, int> o[MAXN];
std::vector<int> magic;

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void add(int x, int n, unsigned int d) {
	for (int i = x; i <= n; i += i & -i) {
		bit[i] += d;
	}
}

unsigned int sum(int x) {
	unsigned int ret = 0;
	for (int i = x; i; i -= i & -i) {
		ret += bit[i];
	}
	return ret;
}

int getSubTree(int x, int anc) {
	int depthDelta = depth[x] - depth[anc] - 1;
	for (int i = 20; i >= 0; i--)
		if ((depth >> i) & 1) x = f[x][i];
	return x;
}

void dfs(int x) {
	s[x] = 1;
	o[x].first = ++cnt;
	p[x] = w[x];
	for (int i = h[x]; i; i = e[i].next) {
		depth[e[i].node] = depth[x] + 1;
		dfs(e[i].node);
		s[x] += s[e[i].node];
	}
	o[x].second = ++cnt;
}

unsigned int getTrueWeight(int x) {
	return w[x] + d[f[x]] + d[f[f[x]]];
}

unsigned int getTrueSum(int x) {
	return p[x] + sum(o[x].first) + d[f[x]] + d[f[f[x]]];
}

int main() {
	freopen("I.in", "r", stdin);
	while (scanf("%d%d", &n, &q) == 2) {
		cnt = 0;
		std::fill(deg + 1, deg + n + 1, 0);
		std::fill(h + 1, h + n + 1, t = 0);
		std::fill(d + 1, d + n + 1, 0);
		size = (int)ceil(sqrt(n));
		for (int i = 1; i < n; i++) {
			scanf("%d", &f[i][0]);
			deg[f[i][0]]++;
			addEdge(f[i][0], i);
		}
		for (int j = 1; j <= 20; j++)
			for (int i = 1; i <= n; i++)
				f[i][j] = f[f[i][j - 1]][j - 1];
		for (int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			w[i] = x;
		}
		magic.clear();
		for (int i = 1; i <= n; i++) {
			val[i] = 0;
			for (int j = h[i]; j; j = e[j].next)
				val[i] += deg[e[j].node];
		}
		dfs(1);
		std::fill(bit + 1, bit + cnt + 1, 0);
		for (int i = 1; i <= n; i++) {
			if (deg[i] > size) {
				magic.push_back(i);
				answer[i] = 0;
				unsigned int sum1 = 0;
				unsigned int sum2 = 0;
				for (int j = h[i]; j; j = e[j].next) {
					sum1 += getTrueSum(e[j].node);
					sum2 += getTrueSum(e[j].node) * s[e[j].node];
				}
				answer[i] = (s[i] + 1) * sum1 - sum2 + getTrueWeight(i) * (s[i] - 1);
			}
		}
		for (int i = 1; i <= q; i++) {
			int op, x, value;
			scanf("%d%d", &op, &x);
			if (op == 1) {
				scanf("%d", &value);
				unsigned int delta = val[x] * ((unsigned int)value);
				d[x] += value;
				bool flag = false;
				for (int j = 0; j < (int)magic.size(); j++) {
					int now = magic[j];
					if (now == x) {
					} else if (o[x].first <= o[now].first && o[now].first <= o[x].second) {
						int sub = getSubTree(now, x);
						answer[now] -= (s[now] + 1) * getTrueSum(sub);
						answer[now] += (s[now] + 1) * 

						answer[now] -= -s[sub] * getTrueSum(sub);
						answer
					} else if (f[now] == x) {
					} else if (f[f[now]] == x) {
						answer[now] += value;
					}
				}
				if (!flag) {
					add(o[x].first, delta);
					add(o[x].second, -delta);
				}
			} else {
				if (deg[x] > size) {
					printf("%d\n", (int)answer[x]);
				} else {
					unsigned int sum1 = 0;
					unsigned int sum2 = 0;
					for (int j = h[x]; j; j = e[j].next) {
						sum1 += getTrueSum(e[j].node);
						sum2 += getTrueSum(e[j].node) * s[e[j].node];
					}
					unsigned int answer = (s[x] + 1) * sum1 - sum2 + getTrueWeight(x) * (s[x] - 1);
					printf("%d\n", (int)answer);
				}
			}
		}
	}
	return 0;
}
