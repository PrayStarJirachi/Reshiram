#include <cstdio>
#include <cmath>

using namespace std;

const double eps = 1E-9;

int X[10000];
int N;
int I[10000];
double best;
int bestS, bestA, bestC;
int S, A, C;

void Gen ()
{
	int l = S;
	for (int i = 0; i < N; i++)
	{
		l = (l * A + C) % 256;
		X[(l + I[i]) % 256]++;
	}
}

int main ()
{
	while (scanf ("%d", &N) == 1)
	{
		if (N == 0) break;
		for (int i = 0; i < N; i++)
		{
			scanf ("%d", &I[i]);
		}
		best = 1E9;
		for (S = 0; S <= 15; S++)
			for (A = 0; A <= 15; A++)
				for (C = 0; C <= 15; C++)
				{
					for (int i = 0; i <= 255; i++)
						X[i] = 0;
					Gen ();
					double ans = 0;
					for (int i = 0; i <= 255; i++)
					{
						if (X[i] > 0)
							ans += - (1.0 * X[i] / N) * log (1.0 * X[i] / N);
					}
//					printf ("%f\n", ans);
					if (ans + eps < best)
					{
						best = ans;
						bestS = S;
						bestA = A;
						bestC = C;
					}
				}
		printf ("%d %d %d\n", bestS, bestA, bestC);
	}
}

