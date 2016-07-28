#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 110001;
const int MAXM = 410001;
const long long INF = 1ll << 50;

struct Edge{
	int node, next, id;
}e[MAXM];

struct Road{
	int x, y, c;
	long long value;
}r[MAXM];

int T, n, m, t, tot, nColor, dfn[MAXN], low[MAXN], a[MAXN], h[MAXN], cut[MAXM], s[MAXN], c[MAXN], counter[MAXN], fa[MAXN];
long long cap[MAXN];
bool v[MAXN];

void addEdge(int x, int y, int id) {
	t++; e[t] = (Edge){y, h[x], id}; h[x] = t;
	t++; e[t] = (Edge){x, h[y], id}; h[y] = t;
}

void tarjan(int x, int fa) {
	dfn[x] = low[x] = ++tot;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].id == fa) continue;
		if (!dfn[e[i].node]) {
			tarjan(e[i].node, e[i].id);
			low[x] = std::min(low[x], low[e[i].node]);
			if (low[e[i].node] > dfn[x]) {
				cut[e[i].id] = true;
			}
		} else {
			low[x] = std::min(low[x], dfn[e[i].node]);
		}
	}
}

void dfs(int x) {
	s[x] = counter[x];
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		fa[e[i].node] = x;
		dfs(e[i].node);
		s[x] += s[e[i].node];
	}
}

void getValue(int x, const int &total) {
	v[x] = true;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		r[e[i].id].value = 1ll * s[e[i].node] * (total - s[e[i].node]) * r[e[i].id].c;
		//printf("pair(%d, %d, %d) = %lld\n", r[e[i].id].x, r[e[i].id].y, r[e[i].id].c, r[e[i].id].value);
		getValue(e[i].node, total);
	}
}

void assign(int x) {
	v[x] = true;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		assign(e[i].node);
	}
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		if (cap[r[e[i].id].y] >= r[e[i].id].value) {
			cap[r[e[i].id].y] -= r[e[i].id].value;
		} else {
			cap[r[e[i].id].x] -= r[e[i].id].value;
		}
	}
}

bool check(const long long &answer) {
	for (int i = 1; i <= n; i++) {
		cap[i] = answer - a[i];
	}
	std::fill(v + 1, v + nColor + 1, false);
	for (int i = 1; i <= nColor; i++) {
		if (v[i]) continue;
		assign(i);
	}
	for (int i = 1; i <= n; i++) {
		if (cap[i] < 0) return false;
	}
	return true;
}

int main() {
	freopen("G.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		std::fill(h + 1, h + n + 1, t = 0);
		std::fill(dfn + 1, dfn + n + 1, tot = 0);
		std::fill(cut + 1, cut + m + 1, false);
		std::fill(fa + 1, fa + n + 1, 0);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%d", &r[i].x, &r[i].y, &r[i].c);
			addEdge(r[i].x, r[i].y, i);
		}
		
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) tarjan(i, 0);
		}
		
		std::fill(h + 1, h + n + 1, t = 0);
		for (int i = 1; i <= m; i++) {
			if (cut[i]) continue;
			addEdge(r[i].x, r[i].y, i);
		}
		nColor = 0;
		std::fill(c + 1, c + n + 1, 0);
		for (int i = 1; i <= n; i++) {
			if (c[i]) continue;
			static int q[MAXN];
			int left = 0, right = 0;
			c[q[++right] = i] = ++nColor;
			while (left < right) {
				left++;
				for (int j = h[q[left]]; j; j = e[j].next) {
					if (c[e[j].node]) continue;
					c[q[++right] = e[j].node] = nColor;
				}
			}
			counter[nColor] = right;
		}
		
		std::fill(h + 1, h + nColor + 1, t = 0);
		for (int i = 1; i <= m; i++) {
			if (!cut[i]) continue;
			addEdge(c[r[i].x], c[r[i].y], i);
			//printf("Bridge[%d, %d] -- [%d, %d]\n", r[i].x, r[i].y, c[r[i].x], c[r[i].y]);
		}
		std::fill(v + 1, v + nColor + 1, false);
		for (int i = 1; i <= nColor; i++) {
			if (v[i]) continue;
			dfs(i);
		}
		for (int i = 1; i <= m; i++) {
			if (!cut[i]) continue;
			if (c[r[i].y] == fa[c[r[i].x]]) {
				std::swap(r[i].x, r[i].y);
			}
		}
		
		std::fill(v + 1, v + nColor + 1, false);
		for (int i = 1; i <= nColor; i++) {
			if (v[i]) continue;
			getValue(i, s[i]);
		}
		
		long long left = 0, right = INF;
		while (left < right) {
			long long middle = left + right >> 1;
			if (check(middle)) right = middle;
			else left = middle + 1;
		}
		printf("Case %d: " LL "\n", cs, left);
	}
	return 0;
}
