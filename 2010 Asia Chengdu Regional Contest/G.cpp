#include <cstdio>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;

struct Edge{
	int node, next;
}e[MAXM];

struct Query{
	int a, b, c, id;
}q[MAXN];

int T, nColor, n, m, t, tot, top, h[MAXN], z[MAXN], dfn[MAXN], low[MAXN], fa[MAXN], color[MAXN];
bool instack[MAXN];

int getfa(int x) {
	return fa[x] ? fa[x] = getfa(fa[x]) : x;
}

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++tot;
	instack[z[++top] = x] = true;
	for (int i = h[x]; i; i = e[i].next) {
		if (!dfn[e[i].node]) {
			tarjan(e[i].node);
			low[x] = std::min(low[x], low[e[i].node]);
		} else if (instack[e[i].node]) {
			low[x] = std::min(low[x], dfn[e[i].node]);
		}
	}
	if (dfn[x] == low[x]) {
		int y;
		nColor++;
		do{
			instack[y = z[top--]] = false;
			color[y] = nColor;
		}
		while (x != y);
	}
}

bool check(const int &answer) {
	static int v[MAXN];
	int total = 0;
	std::fill(v + 1, v + n + 1, false);
	std::fill(fa + 1, fa + n + 1, 0);
	for (int i = 1; i <= answer; i++) {
		if (q[i].c == 1) {
			int fx = getfa(q[i].a), fy = getfa(q[i].b);
			if (fx == fy) continue;
			fa[fx] = fy;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (v[getfa(i)]) continue;
		v[getfa(i)] = ++total;
	}
	std::fill(h + 1, h + 2 * total + 1, t = 0);
	for (int i = 1; i <= answer; i++) {
		if (q[i].c == 0) {
			addEdge(v[getfa(q[i].a)], total + v[getfa(q[i].b)]);
			addEdge(v[getfa(q[i].b)], total + v[getfa(q[i].a)]);
		}
		if (q[i].c == 2) {
			addEdge(total + v[getfa(q[i].a)], v[getfa(q[i].b)]);
			addEdge(total + v[getfa(q[i].b)], v[getfa(q[i].a)]);
		}
	}
	nColor = tot = 0;
	std::fill(dfn + 1, dfn + 2 * total + 1, 0);
	for (int i = 1; i <= 2 * total; i++) {
		if (!dfn[i]) tarjan(i);
	}
	for (int i = 1; i <= total; i++) {
		if (color[i] == color[total + i]) {
			return false;
		}
	}
	return true;
}

int main() {
	freopen("G.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%d", &q[i].a, &q[i].b, &q[i].c);
			q[i].a++;
			q[i].b++;
			q[i].id = i;
		}
		int left = 0, right = m;
		while (left < right) {
			int middle = (left + right >> 1) + 1;
			if (check(middle)) left = middle;
			else right = middle - 1;
		}
		printf("%d\n", left);
	}
	return 0;
}
