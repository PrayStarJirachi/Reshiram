#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 600001;
const int MAXM = 1000001;
const int MOD = 1000000007;

struct Edge{
	int node, next;
}e[MAXM];

struct Road{
	int x, y;
}r[MAXM];

int T, n, m, t, nColor, nPart, tot, top, z[MAXN], h[MAXN], dfn[MAXN], low[MAXN], col[MAXN], w[MAXN], prod[MAXN], size[MAXN], subProd[MAXN], subSum[MAXN], belong[MAXN], prodBlock[MAXN];
bool cut[MAXN], v[MAXN];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

int tarjan(int x) {
	dfn[x] = low[x] = ++tot;
	z[++top] = x;
	int degree = 0;
	for (int i = h[x]; i; i = e[i].next) {
		if (!dfn[e[i].node]) {
			degree++;
			int tmp = top;
			tarjan(e[i].node);
			low[x] = std::min(low[e[i].node], low[x]);
			if (low[e[i].node] >= dfn[x]) {
				cut[x] = true;
				nColor++;
				for (int k = tmp + 1; k <= top; k++) col[z[k]] = nColor;
				col[x] = nColor;
				top = tmp;
			}
		} else {
			low[x] = std::min(low[x], dfn[e[i].node]);
		}
	}
	return degree;
}

void dfs(int x) {
	v[x] = true;
	subProd[x] = prodBlock[x];
	subSum[x] = 0;
	for (int i = h[x]; i; i = e[i].next) {
		if (v[e[i].node]) continue;
		dfs(e[i].node);
		subProd[x] = 1ll * subProd[x] * subProd[e[i].node] % MOD;
		subSum[x] = (subSum[x] + subProd[e[i].node]) % MOD;
	}
}

int fpm(int a, int b) {
	int ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = 1ll * ret * a % MOD;
		a = 1ll * a * a % MOD;
	}
	return ret;
}

int main() {
	freopen("F.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d", &n, &m);
		nColor = tot = top = nPart = 0;
		std::fill(h + 1, h + n + m + 1, t = 0);
		std::fill(dfn + 1, dfn + n + m + 1, 0);
		std::fill(low + 1, low + n + m + 1, 0);
		std::fill(cut + 1, cut + n + m + 1, false);

		for (int i = 1; i <= n; i++) scanf("%d", w + i);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &r[i].x, &r[i].y);
			addEdge(r[i].x, r[i].y);
		}
		std::fill(belong + 1, belong + n + 1, 0);
		for (int i = 1; i <= n; i++) {
			if (belong[i]) continue;
			static int q[MAXN];
			nPart++;
			int left = 0, right = 0;
			belong[q[++right] = i] = nPart;
			while (left < right) {
				left++;
				for (int i = h[q[left]]; i; i = e[i].next) {
					if (belong[e[i].node]) continue;
					belong[q[++right] = e[i].node] = nPart;
				}
			}
		}
		std::fill(size + 1, size + n + 1, 0);
		std::fill(prod + 1, prod + nPart + 1, 1);
		for (int i = 1; i <= n; i++) {
			prod[belong[i]] = 1ll * prod[belong[i]] * w[i] % MOD;
			size[belong[i]]++;
		}

		std::fill(h + 1, h + n + m + 1, t = 0);
		for (int i = 1; i <= m; i++) {
			addEdge(r[i].x, n + i);
			addEdge(r[i].y, n + i);
		}

		for (int i = 1; i <= n + m; i++) {
			if (dfn[i]) continue;
			cut[i] = tarjan(i) > 1;
		}	

		std::vector<int> dis;
		for (int i = 1; i <= n + m; i++) {
			if (i <= n && size[belong[i]] == 1) {
				col[i] = ++nColor;
				dis.push_back(col[i]);
				continue;
			}
			if (cut[i]) col[i] = ++nColor;
			dis.push_back(col[i]);
		}
		std::sort(dis.begin(), dis.end());
		dis.erase(std::unique(dis.begin(), dis.end()), dis.end());
		for (int i = 1; i <= n + m; i++) {
			col[i] = std::lower_bound(dis.begin(), dis.end(), col[i]) - dis.begin() + 1;
		}
		nColor = dis.size();

		std::fill(prodBlock + 1, prodBlock + nColor + 1, 1);
		for (int i = 1; i <= n; i++) {
			prodBlock[col[i]] = 1ll * prodBlock[col[i]] * w[i] % MOD;
		}

		std::fill(h + 1, h + nColor + 1, t = 0);
		for (int i = 1; i <= m; i++) {
			if (col[r[i].x] != col[n + i]) {
				addEdge(col[r[i].x], col[n + i]);
				//printf("AddEdge(%d, %d)\n", col[r[i].x], col[r[i].y]);
			}
			if (col[r[i].y] != col[n + i]) {
				addEdge(col[r[i].y], col[n + i]);
				//printf("AddEdge(%d, %d)\n", col[r[i].x], col[r[i].y]);
			}
		}

		int answer = 0, total = 0;
		for (int i = 1; i <= nPart; i++) {
			total = (total + prod[i]) % MOD;
		}
		std::fill(v + 1, v + nColor + 1, false);
		for (int i = 1; i <= nColor; i++) {
			if (v[i]) continue;
			dfs(i);
		}
		for (int i = 1; i <= n; i++) {
			if (size[belong[i]] == 1) {
				long long tmp = (total - prod[belong[i]]) % MOD;
				answer = (answer + 1ll * i * tmp % MOD) % MOD;
				continue;
			}
			if (!cut[i]) {
				long long tmp = (total - prod[belong[i]]) % MOD;
				tmp = (tmp + 1ll * prod[belong[i]] * fpm(w[i], MOD - 2) % MOD) % MOD;
				answer = (answer + 1ll * i * tmp % MOD) % MOD;
			} else {
				long long tmp = prod[belong[i]];
				tmp = 1ll * tmp * fpm(subProd[col[i]], MOD - 2) % MOD;
				tmp = (tmp + subSum[col[i]]) % MOD;
				tmp = (tmp + total - prod[belong[i]]) % MOD;
				answer = (answer + 1ll * i * tmp % MOD) % MOD;
			}
		}
		answer = (answer % MOD + MOD) % MOD;
		printf("%d\n", answer);
	}
	return 0;
}

