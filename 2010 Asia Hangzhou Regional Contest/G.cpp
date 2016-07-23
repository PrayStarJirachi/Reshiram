#include <cstdio>
#include <algorithm>

const int MAXN = 410001;
const int MAXM = 810001;

struct Edge{
	int node, next;
}e[MAXM];

struct Road{
	int x, y;
}r[MAXM];

namespace QTree{

struct Edge{
	int node, next;
}e[MAXM];

int t, h[MAXN], w[MAXN], d[MAXN], f[MAXN][21], dep[MAXN];
bool v[MAXN];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void dfs(int x) {
	v[x] = true;
	for (int i = h[x]; i; i = e[i].next) {
		if (v[e[i].node]) continue;
		f[e[i].node][0] = x;
		d[e[i].node] = d[x] + w[e[i].node];
		dep[e[i].node] = dep[x] + 1;
		dfs(e[i].node);
	}
}

void init(int n) {
	std::fill(h + 1, h + n + 1, t = 0);
	std::fill(w + 1, w + n + 1, 0);
	std::fill(v + 1, v + n + 1, false);
}

void prepare(int n) {
	for (int i = 1; i <= n; i++) {
		if (v[i]) continue;
		dep[i] = 0;
		d[i] = w[i];
		f[i][0] = 0;
		dfs(i);
	}
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++) {
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
}

int getAnc(int x, int t) {
	for (int i = 0; i <= 20; i++)
		if ((t >> i) & 1) x = f[x][i];
	return x;
}

int getLca(int x, int y) {
	if (dep[x] > dep[y]) x = getAnc(x, dep[x] - dep[y]);
	if (dep[x] < dep[y]) y = getAnc(y, dep[y] - dep[x]);
	if (x == y) return x;
	for (int i = 20; i >= 0; i--) {
		if (f[x][i] == f[y][i]) continue;
		x = f[x][i];
		y = f[y][i];
	}
	return f[x][0];
}

int query(int x, int y) {
	int lca = getLca(x, y);
	//printf("LCA(%d, %d) = %d\n", x, y, lca);
	return d[x] + d[y] - 2 * d[lca] + w[lca];
}

};

int n, m, q, t, tot, top, nColor, z[MAXN], h[MAXN], col[MAXN], dfn[MAXN], low[MAXN];
bool v[MAXN], cut[MAXN];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

int tarjan(int x) {
	int degree = 0;
	dfn[x] = low[x] = ++tot;
	z[++top] = x;
	for (int i = h[x]; i; i = e[i].next) {
		if (!dfn[e[i].node]) {
			int tmp = top;
			degree++;
			tarjan(e[i].node);
			low[x] = std::min(low[x], low[e[i].node]);
			if (low[e[i].node] >= dfn[x]) {
				cut[x] = true;
				nColor++;
				for (int k = tmp + 1; k <= top; k++) {
					col[z[k]] = nColor;
				}
				col[x] = nColor;
				top = tmp;
			}
		} else {
			low[x] = std::min(low[x], dfn[e[i].node]);
		}
	}
	return degree;
}

int main() {
	freopen("G.in", "r", stdin);
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;

		nColor = tot = 0;
		std::fill(dfn + 1, dfn + n + m + 1, 0);
		std::fill(h + 1, h + n + m + 1, t = 0);

		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &r[i].x, &r[i].y);
			addEdge(r[i].x, n + i);
			addEdge(n + i, r[i].y);
		//	printf("Edge(%d, %d) -- %d\n", r[i].x, r[i].y, n + i);
		}

		std::fill(cut + 1, cut + n + m + 1, false);
		for (int i = 1; i <= n; i++) {
			if (dfn[i]) continue;
			cut[i] = (tarjan(i) > 1);
		}

		std::fill(v + 1, v + n + m + 1, false);
		for (int i = 1; i <= n + m; i++) {
			if (cut[i]) {
				col[i] = ++nColor;
				//printf("Cut %d %d\n", i, i <= n);
			}
		}
		/*for (int i = 1; i <= n + m; i++) {
			printf("%d Belong to %d\n", i, col[i]);
		}*/

		//printf("Color Total = %d\n", nColor);
		QTree::init(nColor);
		for (int i = 1; i <= n; i++)
			if (cut[i]) QTree::w[col[i]] = 1;
		for (int i = 1; i <= m; i++) {
			if (col[r[i].x] != col[n + i]) {
				QTree::addEdge(col[r[i].x], col[n + i]);
				//printf("AddEdge(%d, %d)\n", col[r[i].x], col[n + i]);
			}
			if (col[r[i].y] != col[n + i]) {
				QTree::addEdge(col[r[i].y], col[n + i]);
				//printf("AddEdge(%d, %d)\n", col[r[i].y], col[n + i]);
			}
		}

		QTree::prepare(nColor);
		scanf("%d", &q);
		for (int i = 1; i <= q; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			//printf("Query(%d, %d)\n", col[n + x], col[n + y]);
			printf("%d\n", QTree::query(col[n + x], col[n + y]));
		}
	}
	return 0;
}
