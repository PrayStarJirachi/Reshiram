#include <cstdio>
#include <algorithm>

const int MAXT = 1001;
const int MAXN = 1001;
const int INF = ~0u >> 2;

int t, n, cycle[MAXT], d[MAXN], m[MAXN], dp[MAXN][MAXT], z[MAXN];

void update(int &x, int y) {
	if (x > y) x = y;
}

int main() {
	freopen("B.in", "r", stdin);
	while (true) {
		scanf("%d", &t);
		if (t == 0) break;
		for (int i = 1; i <= t; i++) scanf("%d", cycle + i);
		scanf("%d", &n);
		std::fill(z + 1, z + 100 + 1, 25);
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", d + i, m + i);
			z[d[i]] = std::min(z[d[i]], m[i]);
		}
		for (int i = 1; i <= 100; i++)
			for (int j = 1; j <= t; j++)
				dp[i][j] = INF;
		dp[1][1] = 0;
		for (int i = 1; i < 100; i++)
			for (int j = 1; j <= t; j++) {
				if (dp[i][j] == INF) continue;
				int nextCycle = j < t ? j + 1 : 1;
				if (cycle[nextCycle] <= z[i + 1]) {
					update(dp[i + 1][nextCycle], dp[i][j]);
				}
				update(dp[i + 1][1], dp[i][j] + 1);
			}
		int answer = INF;
		for (int i = 1; i <= t; i++)
			update(answer, dp[100][i]);
		printf("%d\n", answer);
	}
	return 0;
}
