#include <cstdio>
#include <algorithm>

const int MAXN = 10001;

int T, n, k, cnt[26];
char s[MAXN];

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d%s", &n, &k, s + 1);
		int answer = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = std::max(1, i - k); j < i; j++) {
				if (s[j] == s[i]) {
					answer++;
					break;
				}
			}
		}
		printf("Case %d: %d\n", cs, answer);
	}
	return 0;
}
