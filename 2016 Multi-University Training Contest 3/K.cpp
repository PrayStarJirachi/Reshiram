#include <cstdio>
#include <algorithm>

const int MAXN = 1100001;

int n, m, cnt[MAXN];
int T, x[MAXN], y[MAXN], d[MAXN];

int main() {
	freopen("K.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
		if (n >= 1000) puts("YES");
		else{
			bool flag = false;
			for (int i = 1; i <= n; i++)
				for (int j = i + 1; j <= n; j++) {
					int tmp = std::abs(x[i] - x[j]) + std::abs(y[i] - y[j]);
					if (cnt[tmp] == cs) {
						flag = true;
					}
					cnt[tmp] = cs;
				}
			if (flag) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
