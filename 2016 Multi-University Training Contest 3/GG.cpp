#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

vector <long long> Edge[200000];
pair <long long, long long> Length[200000];
long long G[200000];

long long DFS (long long x, long long p)
{
	long long ans = 0;
	Length[x].first = Length[x].second = 0;
	for (long long i = 0; i < Edge[x].size (); i++)
	{
		if (Edge[x][i] == p) continue;
		ans += DFS (Edge[x][i], x);
		long long d = Length[Edge[x][i]].first + 2 * G[Edge[x][i]] - 3;
		if (d > Length[x].first)
		{
			Length[x].second = Length[x].first;
			Length[x].first = d;
		}
		else
		{
			if (d > Length[x].second)
				Length[x].second = d;
		}
		/*
		d = Length[Edge[x][i]].second + 2 * G[Edge[x][i]] - 3;
		if (d > Length[x].first)
		{
			Length[x].second = Length[x].first;
			Length[x].first = d;
		}
		else
		{
			if (d > Length[x].second)
				Length[x].second = d;
		}*/
	}
	if (ans == 0)
	{
		G[x] = 1;
		Length[x].first = Length[x].second = 0;
	}
	else
	{
		if (ans % 2 == 0)
			G[x] = 2;
		else
			G[x] = 1;
	}
	return G[x];
}

int main ()
{
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
		long long ans = 0;
		for (long long i = 2; i <= N; i++)
			ans += G[i];
		long long de = 0;
		for (long long i = 1; i <= N; i++)
			if (Edge[i].size () == 1)
				de++;
		if (de % 2 == 1)
		{
			ans -= Length[1].first;
		}
		cout << ans << endl;
	}
}

