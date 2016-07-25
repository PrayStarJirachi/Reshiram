#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 100;
const int MAXM = 2001;
const int MAXS = 300;

int T;
char digit[MAXN];
long long dp[2][MAXM][MAXS][2];

int getDigit(long long x) {
	sprintf(digit + 1, LL, x);
	return strlen(digit + 1);
}

long long calc(long long x) {
	if (x < 0) return 0;
	int length = getDigit(x);
	long long answer = 0;
	memset(dp, 0, sizeof dp);
	dp[0][0][0][1] = 1;
	for (int i = 0; i < length; i++) {
		memset(dp[i & 1 ^ 1], 0, sizeof(dp[i & 1 ^ 1]));
		int maxSum = 9 * i * (i + 1) >> 1;
		for (int j = 0; j <= maxSum; j++)
			for (int k = 0; k <= 9 * i; k++)
				for (int p = 0; p < 2; p++) {
					if (dp[i & 1][j][k][p] == 0) continue;
					int limit = p ? (digit[i + 1] - '0') : 9;
					for (int nextDigit = 0; nextDigit <= limit; nextDigit++) {
						dp[(i + 1) & 1][j + (i + 1) * nextDigit][k + nextDigit][p && (nextDigit == digit[i + 1] - '0')] += dp[i & 1][j][k][p];
					}
				}
	}
	for (int p = 1; p <= length; p++)
		for (int j = 0; j <= 2000; j++)
			for (int k = 0; k <= 9 * length; k++)
				if (j == p * k) {
					answer += dp[length & 1][j][k][0] + dp[length & 1][j][k][1];
				}
	answer -= length - 1;
	return answer;
}

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		long long l, r;
		scanf(LL LL, &l, &r);
		printf(LL "\n", calc(r) - calc(l - 1));
	}
	return 0;
}
