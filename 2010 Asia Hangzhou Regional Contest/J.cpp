#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXA = 30;
const int MAXN = 1001;
const int MAXL = 51;

int n, m, fail[MAXL], trans[MAXL][MAXA];
char word[MAXL];
double p[MAXA], dp[MAXN][MAXL][2];

int main() {
	freopen("J.in", "r", stdin);
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		memset(p, 0, sizeof(p));
		for (int i = 1; i <= n; i++) {
			char alpha[20];
			double prob;
			scanf("%s%lf", alpha, &prob);
			p[alpha[0] - 'a'] = prob;
		}
		scanf("%s", word + 1);
		
		int length = strlen(word + 1);
		fail[0] = -1;
		for (int i = 1; i <= length; i++) {
			int p = fail[i - 1];
			while (p != -1 && word[p + 1] != word[i]) p = fail[p];
			fail[i] = p + 1;
		}
		
		for (int i = 0; i <= length; i++)
			for (int j = 0; j < 26; j++) {
				int p = i;
				while (p != -1 && word[p + 1] != j + 'a') p = fail[p];
				trans[i][j] = p + 1;
				//printf("Tr[%d, %d] = %d\n", i, j, trans[i][j]);
			}
			
		for (int i = 0; i <= m; i++)
			for (int j = 0; j <= length; j++)
				for (int k = 0; k < 2; k++)
					dp[i][j][k] = 0;
					
		dp[0][0][0] = 1;
		for (int i = 0; i < m; i++)
			for (int j = 0; j <= length; j++)
				for (int k = 0; k < 2; k++) {
					for (int c = 0; c < 26; c++) {
						dp[i + 1][trans[j][c]][k || (trans[j][c] == length)] += dp[i][j][k] * p[c];
				}
			}
			
		double answer = 0;
		for (int j = 0; j <= length; j++) answer += dp[m][j][1];
		printf("%.2f%%\n", answer * 100);
	}
	return 0;
}
