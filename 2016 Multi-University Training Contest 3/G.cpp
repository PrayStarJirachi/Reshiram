#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

vector <int> Edge[110000];
long long DP[110000][3];
long long G[110000];

long long DFS (long long x, long long p)
{
	long long ans = 0;
	for (long long i = 0; i < Edge[x].size (); i++)
	{
		if (Edge[x][i] == p) continue;
		ans += DFS (Edge[x][i], x);
	}
	if (ans == 0)
		G[x] = 1;
	else
	{
		if (ans % 2 == 0)
			G[x] = 2;
		else
			G[x] = 1;
	}
	return G[x];
}

void dp (long long x, long long p)
{
	DP[x][0] = DP[x][1] = DP[x][2] = 0;
	for (long long i = 0; i < Edge[x].size (); i++)
	{
		if (Edge[x][i] == p) continue;
		dp (Edge[x][i], x);
		DP[x][0] += (DP[Edge[x][i]][0] + G[Edge[x][i]]);
	}
	for (long long i = 0; i < Edge[x].size (); i++)
	{
		if (Edge[x][i] == p) continue;
		long long q = DP[x][0] - G[Edge[x][i]] + (3 - G[Edge[x][i]]);
		if (DP[x][1] == 0 || DP[x][1] > q) DP[x][1] = q;
		long long r = DP[x][0] - DP[Edge[x][i]][0] + DP[Edge[x][i]][1] - G[Edge[x][i]] + (3 - G[Edge[x][i]]);
		if (DP[x][1] == 0 || DP[x][1] > r) DP[x][1] = r;
	}

}

int main ()
{
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
	long long T;
	long long N;
	cin >> T;
	for (long long t = 1; t <= T; t++)
	{
		cin >> N;
		for (long long i = 1; i <= N; i++)
			Edge[i].clear ();
		for (long long i = 0; i < N - 1; i++)
		{
			long long a, b;
			cin >> a >> b;
			Edge[a].push_back (b);
			Edge[b].push_back (a);
		}
		DFS (1, -1);
		dp (1, -1);
		long long de = 0;
		for (long long i = 1; i <= N; i++)
			if (Edge[i].size () == 1)
				de++;
//		printf ("%d\n", DP[8][2]);
		if (de % 2 == 1)
			cout << DP[1][1] << " " << DP[1][0] << endl;
		else
			cout << DP[1][0] << endl;
	}
}

