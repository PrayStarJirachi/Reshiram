#include <cstdio>
#include <cmath>

using namespace std;

int TT, N, Q;
int Chps, T[200], C[200], R[200], chc;

bool Valid (double times)
{
	double t = 0;
	for (int i = 0; i < N; i++)
		if (C[i] * times > 1.0 * R[i] * T[i])
			t += (1.0 * C[i] * times / T[i] - 1.0 * R[i]);
	if (t > times * Chps * chc) return false;
	return true;
}

int main ()
{
	int t;
	while (scanf ("%d%d", &N, &Q) == 2)
	{
		if (N == 0 && Q == 0) break;
		t++;
		scanf ("%d", &Chps);
		for (int i = 0; i < N; i++)
			scanf ("%d%d%d", &C[i], &T[i], &R[i]);
		printf ("Case %d:\n", t);
		double a = 0;
		for (int i = 0; i < N; i++)
			a += 1.0 * C[i] / (T[i] * Chps);
		printf ("%d\n", (int) ceil (a));
		for (int q = 0; q < Q; q++)
		{
			scanf ("%d", &chc);
			double l = 0, r = 110000;
			for (int tr = 0; tr < 50; tr++)
			{
				double m = (l + r) / 2;
				if (Valid (m))
					l = m;
				else
					r = m;
			}
			if ((l + r) / 2 > 100000)
				printf ("-1.000\n");
			else
				printf ("%.3f\n", (l + r) / 2);
		}
	}
}

