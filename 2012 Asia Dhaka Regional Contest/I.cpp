#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 51;
const int MAXH = 2501;
const int INF = ~0u >> 2;

int T, n, k, dp[MAXN][MAXN][MAXH], tmp[MAXN][MAXH];

std::pair<int, int> p[MAXN];

bool cmp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return b.first * a.second > a.first * b.second;
}

int main() {
	freopen("I.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d", &n, &k);
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &p[i].first, &p[i].second);
			sum += p[i].second;
		}
		std::sort(p + 1, p + n + 1, cmp);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= k; j++)
				for (int h = 0; h <= sum; h++)
					dp[i][j][h] = tmp[j][h] = -INF;
		dp[0][0][0] = tmp[0][0] = 0;
		for (int i = 1, sum = 0; i <= n; i++) {
			sum += p[i].second;
			for (int j = 1; j <= k; j++) {
				for (int h = p[i].second; h <= sum; h++) {
					dp[i][j][h] = tmp[j - 1][h - p[i].second] + p[i].first * p[i].second + 2 * p[i].first * (h - p[i].second);
				}
			}
			for (int j = 1; j <= k; j++)
				for (int h = p[i].second; h <= sum; h++)
					tmp[j][h] = std::max(tmp[j][h], dp[i][j][h]);
		}
		int answer = 0;
		for (int i = 1; i <= n; i++) {
			for (int h = 0; h <= sum; h++) {
				answer = std::max(answer, dp[i][k][h]);
			//	printf("Dp[%d, %d, %d] = %d\n", i, k, h, dp[i][k][h]);
			}
		}
		printf("Case %d: %d\n", cs, answer);
	}
	return 0;
}
