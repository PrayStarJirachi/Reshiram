#include <cstdio>
#include <algorithm>

const int MAXE = 911;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int T, n, m, a[MAXE][MAXE], id[MAXE][MAXE], x[MAXE], map[MAXE][MAXE];

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		int n, m, tot = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				id[i][j] = ++tot;
		for (int i = 1; i <= tot; i++)
			for (int j = 1; j <= tot + 1; j++)
				a[i][j] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				scanf("%d", &a[id[i][j]][tot + 1]);
				map[i][j] = a[id[i][j]][tot + 1];
				a[id[i][j]][tot + 1] = (3 - a[id[i][j]][tot + 1]) % 3;
				a[id[i][j]][id[i][j]] = (a[id[i][j]][id[i][j]] + 2) % 3;
				for (int d = 0; d < 4; d++) {
					int nx = i + dx[d], ny = j + dy[d];
					if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
						a[id[i][j]][id[nx][ny]]++;
					}
				}
			}
		for (int h = 1; h <= tot; h++) {
			if (a[h][h] == 0) {
				for (int i = h + 1; i <= tot; i++)
					if (a[i][h] != 0) {
						for (int j = h; j <= tot + 1; j++) {
							std::swap(a[i][j], a[h][j]);
						}
						break;
					}
			}
			if (a[h][h] == 0) continue;
			for (int i = h + 1; i <= tot; i++) {
				if (a[i][h] == 0) continue;
				int t = a[i][h] * a[h][h] % 3;
				for (int j = h; j <= tot + 1; j++) {
					a[i][j] = (a[i][j] - a[h][j] * t) % 3;
					if (a[i][j] < 0) a[i][j] += 3;
				}
			}
		}
		/*for (int i = 1; i <= tot; i++) {
			for (int j = 1; j <= tot; j++)
				printf("%d ", a[i][j]);
			printf(" | %d\n", a[i][tot + 1]);
		}*/
		for (int h = tot; h >= 1; h--) {
			x[h] = a[h][tot + 1];
			for (int i = h + 1; i <= tot; i++) {
				x[h] = (x[h] - a[h][i] * x[i]) % 3;
			}
			x[h] = (x[h] * a[h][h]) % 3;
			x[h] = (x[h] % 3 + 3) % 3;
		}
		std::vector<std::pair<int, int> > answer;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				for (int k = 1; k <= x[id[i][j]]; k++) {
					answer.push_back(std::make_pair(i, j));
				}
		printf("%d\n", (int)answer.size());
		for (int i = 0; i < (int)answer.size(); i++) {
			printf("%d %d\n", answer[i].first, answer[i].second);
			/*map[answer[i].first][answer[i].second] = (map[answer[i].first][answer[i].second] + 2) % 3;
			for (int d = 0; d < 4; d++) {
				int nx = answer[i].first + dx[d];
				int ny = answer[i].second + dy[d];
				if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
					map[nx][ny] = (map[nx][ny] + 1) % 3;
				}
			}*/
		}
		/*for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				printf("%d%c", map[i][j], " \n"[j == m]);*/
	}
}
