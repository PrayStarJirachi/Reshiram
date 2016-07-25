#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int mx[4] = {1, 0, 0, -1}, my[4] = {0, -1, 1, 0};
int Trans[4] = {1, 0, 2, 3};

int T;
int Map1[10][10], Map2[10][10];
char Vis[10][10][10][10];
pair <pair <int, int>, pair <int, int> > Pre[10][10][10][10];
int ans[1000], anst = 0;

char Tochar (int x)
{
	if (x == 0) return 'D';
	if (x == 1) return 'L';
	if (x == 2) return 'R';
	return 'U';
}

int main ()
{
	scanf ("%d", &T);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			scanf ("%d", &Map1[i][j]);
	for (int t = 0; t < T - 1; t++)
	{
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				scanf ("%d", &Map2[i][j]);
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 6; k++)
					for (int l = 0; l < 6; l++)
						Vis[i][j][k][l] = -1;
		queue <pair <pair <int, int>, pair <int, int> > > que;
		int sx1, sy1, sx2, sy2, ex1, ey1, ex2, ey2;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
			{
				if ((Map1[i][j] & (1 << 5)) > 0)
				{
					sx1 = i;
					sy1 = j;
				}
				if ((Map1[i][j] & (1 << 6)) > 0)
				{
					ex1 = i;
					ey1 = j;
				}
				if ((Map2[i][j] & (1 << 5)) > 0)
				{
					sx2 = i;
					sy2 = j;
				}
				if ((Map2[i][j] & (1 << 6)) > 0)
				{
					ex2 = i;
					ey2 = j;
				}
			}
		que.push (make_pair (make_pair (sx1, sy1), make_pair (sx2, sy2)));
		while (!que.empty ())
		{
			int x1 = que.front ().first.first, y1 = que.front ().first.second, x2 = que.front ().second.first, y2 = que.front ().second.second;
			if (x1 == ex1 && y1 == ey1 && x2 == ex2 && y2 == ey2)
			{
				anst = 0;
				while (! (x1 == sx1 && y1 == sy1 && x2 == sx2 && y2 == sy2))
				{
//					puts ("Die");
					ans[anst++] = Vis[x1][y1][x2][y2];
					int nx1 = Pre[x1][y1][x2][y2].first.first;
					int ny1 = Pre[x1][y1][x2][y2].first.second;
					int nx2 = Pre[x1][y1][x2][y2].second.first;
					int ny2 = Pre[x1][y1][x2][y2].second.second;
					x1 = nx1; x2 = nx2; y1 = ny1; y2 = ny2;
				}
				for (int i = anst - 1; i >= 0; i--)
					putchar (Tochar (ans[i]));
				puts ("");
				break;
			}
			for (int i = 0; i < 4; i++)
			{
				int nx1 = x1, ny1 = y1, nx2 = x2, ny2 = y2;
				if ((Map1[x1][y1] & (1 << Trans[i])) == 0)
				{
					nx1 += mx[i];
					ny1 += my[i];
				}
				if ((Map2[x2][y2] & (1 << Trans[i])) == 0)
				{
					nx2 += mx[i];
					ny2 += my[i];
				}
				if (nx1 < 0 || ny1 < 0 || nx1 >= 6 || ny1 >= 6 || nx2 < 0 || ny2 < 0 || nx2 >=6 || ny2 >= 6) continue;
				if ((Map1[nx1][ny1] & (1 << 4)) == 0 || (Map2[nx2][ny2] & (1 << 4)) == 0) continue;
				if (Vis[nx1][ny1][nx2][ny2] != -1) continue;
				Vis[nx1][ny1][nx2][ny2] = i;
				Pre[nx1][ny1][nx2][ny2] = que.front ();
				que.push (make_pair (make_pair (nx1, ny1), make_pair (nx2, ny2)));
			}
			que.pop ();
		}
		if (que.empty ())
			puts ("-1");
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				Map1[i][j] = Map2[i][j];
	}
}

