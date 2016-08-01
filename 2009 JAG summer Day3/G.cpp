#include <cmath>
#include <cstdio>
#include <algorithm>

const int INF = ~0u >> 2;
const int MAXN = 201;
const long double EPS = 1e-9;

int n, s, t, w[MAXN], deg[MAXN], a[MAXN][MAXN], g[MAXN][MAXN];
long double e[MAXN][MAXN], x[MAXN];

int main() {
	freopen("G.in", "r", stdin);
	while (true) {
		scanf("%d%d%d", &n, &s, &t);
		if (n == 0 && s == 0 && t == 0) break;
		for (int i = 1; i <= n; i++) scanf("%d", w + i);
		std::fill(deg + 1, deg + n + 1, 0);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &a[i][j]);
				if (a[i][j] == 0) a[i][j] = INF;
				g[i][j] = a[i][j];
			}
		}
		for (int i = 1; i <= n; i++) g[i][i] = 0;
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
		if (g[s][t] == INF) {
			puts("impossible");
			continue;
		}
		for (int i = 1; i <= n; i++) {
			if (w[i]) {
				for (int j = 1; j <= n; j++) {
					if (a[i][j] + g[j][t] == g[i][t]) {
						deg[i]++;
					}
				}
			} else {
				for (int j = 1; j <= n; j++) {
					if (a[i][j] == INF) continue;
					deg[i]++;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n + 1; j++) {
				e[i][j] = 0;
			}
		}
		for (int i = 1; i <= n; i++) e[i][i] = 1;
		for (int i = 1; i <= n; i++) {
			if (w[i]) {
				for (int j = 1; j <= n; j++) {
					if (a[i][j] + g[j][t] == g[i][t]) {
				//		printf("(%d, %d)\n", i, j);
						e[i][j] -= 1.0 / deg[i];
						e[i][n + 1] += 1.0 * a[i][j] / deg[i];
					}
				}
			} else {
				for (int j = 1; j <= n; j++) {
					if (a[i][j] == INF) continue;
				//	printf("(%d, %d)\n", i, j);
					e[i][j] -= 1.0 / deg[i];
					e[i][n + 1] += 1.0 * a[i][j] / deg[i];
				}
			}
		}
		std::fill(e[t] + 1, e[t] + n + 1 + 1, 0);
		e[t][t] = 1;
		/*for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				printf("%7.3f ", (double)e[i][j]);
			printf("| %7.3f\n", (double)e[i][n + 1]);
		}*/
		for (int h = 1; h <= n; h++) {
			for (int i = h + 1; i <= n; i++)
				if (fabs(e[i][h]) > fabs(e[h][h])) {
					for (int j = 1; j <= n + 1; j++) {
						std::swap(e[i][j], e[h][j]);
					}
				}
			if (fabs(e[h][h]) < EPS) continue;
			for (int i = h + 1; i <= n; i++) {
				double k = e[i][h] / e[h][h];
				for (int j = h; j <= n + 1; j++) {
					e[i][j] -= e[h][j] * k;
				}
			}
		}
		for (int i = 1; i <= n; i++) x[i] = 0;
		for (int h = n; h >= 1; h--) {
			if (fabs(e[h][h]) < EPS) continue;
			x[h] = e[h][n + 1];
			for (int i = h + 1; i <= n; i++) {
				x[h] -= e[h][i] * x[i];
			}
			x[h] /= e[h][h];
		}
		printf("%.20f\n", (double)x[s]);
	}
	return 0;
}
