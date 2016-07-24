#include <cstdio>
#include <map>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const int MOD = 1E9 + 7;

int T;
int N;
pair <int, int> P[2000];
int mul[3000];
pair <pair <int, int>, int> Dir[2000];
bool used[2000][2000];
map <pair <int, int>, int> Pt;
int Cnt[2000], PCnt[2000];

int main ()
{
	freopen ("E.in", "r", stdin);
	mul[0] = 1;
	for (int i = 1; i <= 2000; i++)
		mul[i] = (mul[i - 1] * 2) % MOD;
	scanf ("%d", &T);
	for (int t = 0; t < T; t++)
	{
		scanf ("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				used[i][j] = 0;
		Pt.clear ();
		for (int i = 0; i < N; i++)
			Cnt[i] = PCnt[i] = 0;
		for (int i = 0; i < N; i++)
		{
			scanf ("%d%d", &P[i].first, &P[i].second);
		}
		for (int i = 0; i < N; i++)
			Pt[P[i]]++;
		sort (P, &P[N]);
		N = unique (P, &P[N]) - P;
		for (int i = 0; i < N; i++)
		{
			PCnt[i] = Pt[P[i]];
//			printf ("%d\n", PCnt[i]);
		}
//		puts ("");
		int ans = 0;
		for (int i = 0; i < N; i++)
		{
			int C = 0;
			for (int j = i + 1; j < N; j++)
			{
				int dx = P[i].first - P[j].first, dy = P[i].second - P[j].second;
				int tmp = __gcd (abs (dx), abs (dy));
				dx /= tmp; dy /= tmp;
				if (dx < 0)
				{
					dx = -dx;
					dy = -dy;
				}
				if (dx == 0 && dy < 0)
				{
					dy = -dy;
				}
				Dir[C].first = make_pair (dx, dy);
				Dir[C++].second = j;
			}
			sort (Dir, &Dir[C]);
			for (int j = 0; j < C;)
			{
				if (used[i][Dir[j].second]) 
				{
					j++;
					continue;
				}
				int r;
				for (r = j; r < C && Dir[r].first == Dir[j].first; r++);
				int sum = PCnt[i];
				for (int k = j; k < r; k++)
				{
					for (int l = j; l < k; l++)
					{
						used[Dir[k].second][Dir[l].second] = used[Dir[l].second][Dir[k].second] = true;
					}
					used[i][Dir[k].second] = used[Dir[k].second][i] = true;
					sum += PCnt[Dir[k].second];
					Cnt[Dir[k].second]++;
				}
				Cnt[i]++;
				ans += mul[sum] - sum - 1;
				ans %= MOD;
				j = r;
			}
		}
		for (int i = 0; i < N; i++)
		{
			if (Cnt[i] == 0)
			{
				ans += mul[PCnt[i]]- PCnt[i] - 1;
				ans %= MOD;
			}
			if (Cnt[i] > 1)
			{
				ans -= (((1LL * (mul[PCnt[i]] - PCnt[i] - 1) * (Cnt[i] - 1)) % MOD) + MOD) % MOD;
				ans = (ans + MOD) % MOD;
			}
		}
		printf ("%d\n", ans);
	}
}

