#include <cstdio>
#include <algorithm>

using namespace std;

double DP[20][30][30][60][3];
int DPT[20][30][30][60][3];
int t;
int T, N;
double B[2][3], D[2][3];

double fix (double f)
{
	if (f < 0) return 0;
	if (f > 1) return 1;
	return f;
}

double dp (int i, int j, int k, int l, int tl, int p)
{
	if (DPT[i][j][k][l][tl] == t) return DP[i][j][k][l][tl];
	double ans = 0;
	double f1 = B[p][0] - D[p][0] * (i + j + k + l + (tl > 0));
	double f2 = B[p][1] - D[p][1] * (i + j + k + l + (tl > 0));
	double f3 = B[p][2] - D[p][2] * (i + j + k + l + (tl > 0));
	f1 = fix (f1); f2 = fix (f2); f3 = fix (f3);
	if (tl < 2)
	{
		if (i > 1)
		{
			ans = max (ans, (1 - dp (i - 1, j + 1, k, l, tl + 1, 1 - p)) * (f1));
			ans = max (ans, (1 - dp (i - 1, j, k + 1, l, tl + 1, 1 - p)) * (f2));
		}
		if (k > 0)
			ans = max (ans, (1 - dp (i, j, k - 1, l + 1, tl + 1, 1 - p)) * (f3));
	}
	else
	{
		if (i > 1)
		{
			ans = max (ans, (1 - dp (i, j + 1, k, l, 0, 1 - p)) * (f1));
			ans = max (ans, (1 - dp (i, j, k + 1, l, 0, 1 - p)) * (f2));
		}
		if (k > 0)
			ans = max (ans, (1 - dp (i + 1, j, k - 1, l + 1, 0, 1 - p)) * (f3));
	}
	DP[i][j][k][l][tl] = ans;
	DPT[i][j][k][l][tl] = t;
	return DP[i][j][k][l][tl];
}

int main ()
{
	scanf ("%d", &T);
	for (t = 1; t <= T; t++)
	{
		scanf ("%d", &N);
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 3; j++)
				scanf ("%lf%lf", &B[i][j], &D[i][j]);
		printf ("%.4f\n", dp (N, 0, 0, 0, 0, 0));
	}
}

