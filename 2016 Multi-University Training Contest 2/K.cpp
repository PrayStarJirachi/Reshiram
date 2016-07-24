#include <cstdio>

using namespace std;

int T, N, A[100100];

int main ()
{
	scanf ("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf ("%d", &N);
		for (int i = 0; i < N; i++)
			scanf ("%d", &A[i]);
		int oddc = 0;
		for (int i = 0; i < N; i++)
			if (A[i] % 2) oddc++;
		int evenc = 0;
		for (int i = 0; i < N; i++)
			evenc += A[i] / 2;
		if (oddc > 0)
			printf ("%d\n", (evenc / oddc) * 2 + 1);
		else
			printf ("%d\n", evenc * 2);
	}
}

