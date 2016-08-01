#include <cstdio>
#include <iostream>

using namespace std;

int n, c[10005];

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i ++)
			scanf("%d", &c[i]);
		if (n == 1)
		{
			printf ("%.8f\n", (double) c[1]);
			continue;
		}
		double p = 0;
		double ans = 0;
		for (int i = 1; i <= n; i ++) {
			double x = 1.0 / n;
			x *= 1.0 * (i - 1) / (n - 1);
			x *= 1.0 * (i - 2) / (n - 2);
			p += x;
		}
		for (int i = 2; i < n; i ++) ans += p * c[i];
		p = 0;
		for (int i = 1; i <= n; i ++) {
			double x = 1.0 / n * (i - 1) / (n - 1);
			p += x;
		}
		ans += p * c[1] + p * c[n];
		printf("%.8f\n", ans);
	}
	return 0;
}
