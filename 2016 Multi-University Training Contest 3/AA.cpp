#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

char s[100005];

int main() {
	while (scanf("%s", s + 1) == 1) {
		int n = strlen(s + 1);
		if (n >= 15) {
			puts("TAT");
			continue;
		}
		long long sum = 0;
		for (int i = 1; i <= n; i ++)
			sum = sum * 10 + s[i] - '0';
		if (sum == 0)
		{
			puts ("TAT");
			continue;
		}
		int times = 0;
		while (sum > 1) {
			times ++;
			if (times > 5) break;
			long long root = sqrt(sum);
			for (long long tmp = root - 1; tmp <= root + 1; tmp ++) {
				if ((tmp + 1) * (tmp + 1) > sum) {
					root = tmp;
					break;
				}
			}
			sum = root;
//			printf("%d %lld\n", times, sum);
		}
//		cout << "sum = " << sum << endl;
		
		if (times <= 5) printf("%d\n", times);
		else puts("TAT");
	}
	return 0;
}
