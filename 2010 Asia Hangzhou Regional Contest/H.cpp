#include <cstdio>
#include <vector>
#include <algorithm>

const int INF = ~0u >> 2;
const int MAXN = 1001;

int n, m;
std::vector<int> g[MAXN];

int main() {
	freopen("H.in", "r", stdin);
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 1; i <= n * n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			g[x].push_back(y);
		}
		
		for (int i = 1; i <= n; i++) {
			std::sort(g[i].begin(), g[i].end());
		}
		
		int answer = INF;
		for (int h = 1; h <= m - n + 1; h++) {
			int tmp = 0;
			for (int i = 1; i <= n; i++)
				for (int j = 0; j < n; j++)
					tmp += std::abs(g[i][j] - (h + j));
			answer = std::min(answer, tmp);
		}
		
		printf("%d\n", answer);
	}
	return 0;
}
