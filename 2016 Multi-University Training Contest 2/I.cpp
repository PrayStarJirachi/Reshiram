#include <cstdio>
#include <algorithm>

using namespace std;

int T;
int N;
int M;
int A[200], fixd[200];

int main ()
{
	scanf ("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf ("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
		{
			A[i] = 0;
			fixd[i] = 0;
		}
		for (int i = 0; i < M; i++)
		{
			int a, b;
			scanf ("%d%d", &a, &b);
			A[a] = b;
			fixd[a] = 1;
		}
		int min = 0;
		for (int i = N; i >= 1; i--)
		{
			if (fixd[i])
			{
				min = A[i];
				continue;
			}
			A[i] = min;
		}
		if (fixd[1] == 0)
			A[1] = 100;
		if (fixd[2] == 0)
			A[2] = A[1];
		int D = A[1] + A[2], S = 0;
		for (int i = 1; i <= N; i++) S += A[i];
		int ta = __gcd (D, S);
		D /= ta;
		S /= ta;
		printf ("%d/%d\n", D, S);
	}
}

