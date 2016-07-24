#include <cstdio>
#include <algorithm>

using namespace std;

int T, N, M;
int Cnt[3000000];
int A[30000];
int tot;

struct opr
{
	int x;
	int y1;
	int y2;
	int tp;
};

bool operator < (const opr &a, const opr &b)
{
	if (a.x == b.x) return a.tp < b.tp;
	return a.x < b.x;
}

opr O[3000000];
int OC = 0;
bool ans[3000000];

int lowbit (int x)
{
	return x & (-x);
}

int Query (int x)
{
	int ans = 0;
	while (x > 0)
	{
		ans += Cnt[x];
		x -= lowbit (x);
	}
	return ans;
}

int Add (int x, int d)
{
	while (x < tot)
	{
		Cnt[x] += d;
		x += lowbit (x);
	}
}

int main ()
{
	freopen ("H.in", "r", stdin);
	scanf ("%d", &T);
	for (int t = 0; t < T; t++)
	{
		scanf ("%d%d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf ("%d", &A[i]);
		OC = 0;
		vector <int> dis;
		for (int i = 0; i < N; i++)
		{
			int S0 = 0, S1 = 0;
			for (int j = i + 1; j < N; j++)
			{
				int x1 = S0, x2 = S0, y1 = S1, y2 = S1;
				if (i % 2 == 0)
					x2 += A[i];
				else
					y2 += A[i]; 
				if (j % 2 == 0)
					x2 += A[j];
				else
					y2 += A[j];
//				printf ("%d %d %d %d\n", x1, y1, x2, y2);
				O[OC].x = x1;
				O[OC].y1 = y1;
				O[OC].y2 = y2;
				O[OC].tp = 0;
				OC++;
				O[OC].x = x2;
				O[OC].y1 = y1;
				O[OC].y2 = y2;
				O[OC].tp = 2;
				OC++;
				dis.push_back (y1);
				dis.push_back (y2);
				if (j % 2 == 0)
					S0 += A[j];
				else
					S1 += A[j];
			}
		}
		for (int i = 0; i < M; i++)
		{
			int a, b;
			scanf ("%d%d", &a, &b);
			O[OC].x = a;
			O[OC].y1 = b;
			O[OC].y2 = i;
			O[OC].tp = 1;
			dis.push_back (O[OC].y1);
			OC++;
		}
		sort (dis.begin (), dis.end ());
		dis.erase (unique (dis.begin (), dis.end ()), dis.end ());
		tot = dis.size () + 10;
		for (int i = 0; i < OC; i++)
			if (O[i].tp == 1)
				O[i].y1 = lower_bound (dis.begin (), dis.end (), O[i].y1) - dis.begin () + 1;
			else
			{
				O[i].y1 = lower_bound (dis.begin (), dis.end (), O[i].y1) - dis.begin () + 1;
				O[i].y2 = lower_bound (dis.begin (), dis.end (), O[i].y2) - dis.begin () + 1;
			}
		sort (O, &O[OC]);
		for (int o = 0; o < OC; o++)
		{
			if (O[o].tp == 0)
			{
				Add (O[o].y1, 1);
				Add (O[o].y2 + 1, -1);
			}
			if (O[o].tp == 2)
			{
				Add (O[o].y1, -1);
				Add (O[o].y2 + 1, 1);
			}
			if (O[o].tp == 1)
			{
				int k = Query (O[o].y1);
//				printf ("%d\n", k);
				if (k > 0)
					ans[O[o].y2] = true;
				else
					ans[O[o].y2] = false;
			}
		}
		for (int i = 0; i < M; i++)
			printf ("%d", ans[i]);
		puts ("");
	}
}

