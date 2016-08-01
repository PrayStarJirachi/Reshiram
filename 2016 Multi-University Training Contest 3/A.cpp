#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

const double EPS = 1e-5;
const int MAXN = 100001;

char s[MAXN];

int main() {
	freopen("A.in", "r", stdin);
	while (scanf("%s", s + 1) == 1) {
		int length = strlen(s + 1);
		if (length > 12) {
			puts("TAT");
			continue;
		}
		long long number = 0;
		for (int i = 1; i <= length; i++) number = number * 10 + s[i] - '0';
		long long tmp = 2, flag = 0;
		for (int i = 1; i <= 5; i++) {
			tmp *= tmp;
			if (number < tmp) {
				flag = i;
				break;
			}
		}
		if (flag == 0) puts("TAT");
		else printf("%d\n", (int)flag);
	}
	return 0;
}
