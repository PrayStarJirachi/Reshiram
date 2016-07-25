#include <cstdio>
#include <algorithm>

using namespace std;

int diff (int a, int b)
{
	int t = a ^ b;
	int ans = 0;
	while (t > 0)
	{
		ans++;
		t -= (t & (-t));
	}
	return ans;
}

int T, N, M;
int A[1000], B[1000];

int main ()
{
	scanf ("%d", &T);
	for (int t = 0; t < T; t++)
	{
		scanf ("%d%d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf ("%d", &A[i]);
		for (int i = 0; i < M; i++)
		{
			scanf ("%d", &B[i]);
			int best = 1E9, bestA = 1E9;
			for (int j = 0; j < N; j++)
			{
				int g = diff (A[j], B[i]);
				if (best > g || (best == g && bestA > A[j]))
				{
					best = g;
					bestA = A[j];
				}
			}
			printf ("%d\n", bestA);
		}
	}
}

