#include <cstdio>
#include <algorithm>

using namespace std;

double DP[40][20000][2];
int DPT[40][20000][2];
int N, M;
double P[10][40];
bool Pre[40];
int t;
int L;
int MN;

int aEncode (int *a)
{
	int ans = 0;
	for (int i = N - 1; i >= 0; i--)
	{
		ans *= L;
		ans += a[i];
	}
	return ans;
}

double dp (int x, int m, int k)
{
	if (x >= M) return 0;
	if (DPT[x][m][k] == t) return DP[x][m][k];
	int a[5];
	int o = m;
	for (int i = 0; i < N; i++)
	{
		a[i] = o % L;
		o /= L;
	}
	int s = M % N;
	for (int i = 0; i < N; i++)
		if (a[i] == MN + 1) s--;
	double ans = 0;
	for (int i = 0; i < N; i++)
	{
		if (a[i] < MN || (a[i] == MN && s > 0))
		{
			a[i]++;
			if (Pre[x] && k == 0)
				ans = max (dp (x + 1, aEncode (a), 0), ans);
			else
				ans = max (dp (x + 1, aEncode (a), 0) * (1 - P[i][x]) + (dp (x + 1, aEncode (a), 1) + 1) * P[i][x], ans);
			a[i]--;
		}
	}
	DP[x][m][k] = ans;
	DPT[x][m][k] = t;
	return ans;
}

int main ()
{
	int T;
	scanf ("%d", &T);
	for (t = 1; t <= T; t++)
	{
		scanf ("%d%d", &N, &M);
		int K;
		scanf ("%d", &K);
		for (int j = 0; j < M; j++)
			Pre[j] = false;
		for (int j = 0; j < K; j++)
		{
			int l;
			scanf ("%d", &l);
			Pre[l - 1] = true;
		}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				scanf ("%lf", &P[i][j]);
		L = M / N + 2;
		MN = M / N;
		printf ("Case %d: %.4f\n", t, dp (0, 0, 0));
	}
}

