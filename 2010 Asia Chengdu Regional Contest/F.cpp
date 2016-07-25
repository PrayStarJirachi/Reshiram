#include <cstdio>
#include <cmath>

using namespace std;

int T, N;
int A[11000], B[11000], C[11000];

bool Valid (long double m)
{
	long double l = 0, r = 1000;
	for (int i = 0; i < N; i++)
	{
		long double c = 1.0 * C[i] - m;
		if (A[i] != 0)
		{
			long double det = 1.0 * B[i] * B[i] - 4.0 * A[i] * c;
			if (det < 0)
				return true;
			else
			{
				long double l1 = (-1.0 * B[i] - sqrt (det)) / (2.0 * A[i]);
				long double r1 = (-1.0 * B[i] + sqrt (det)) / (2.0 * A[i]);
				if (l1 > l) l = l1;
				if (r1 < r) r = r1;
			}
		}
		else
		{
			if (B[i] == 0)
			{
				if (c <= 0)
					continue;
				return true;
			}
			if (B[i] > 0)
			{
				long double r1 = - c / B[i];
				if (r > r1) r = r1;
			}
			else
			{
				long double l1 = - c / B[i];
				if (l < l1) l = l1;
			}
		}
	}
	if (l <= r) return false;
	return true;
}

long double fix (long double x)
{
	if (fabs (x) < 1E-6)
		return 0;
	return x;
}

int main ()
{
	scanf ("%d", &T);
	for (int t = 0; t < T; t++)
	{
		scanf ("%d", &N);
		for (int i = 0; i < N; i++)
			scanf ("%d%d%d", &A[i], &B[i], &C[i]);
		long double l = -1E9, r = 1E9;
		for (int i = 0; i < 50; i++)
		{
			long double m = (l + r) / 2;
//			printf ("%f %d\n", m, Valid (m));
			if (Valid (m))
				l = m;
			else
				r = m;
		}
		printf ("%.4f\n", (double) fix ((l + r) / 2));
	}
}

