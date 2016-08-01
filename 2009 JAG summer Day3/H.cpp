#include <cstdio>
#include <queue>

using namespace std;

int mx[5] = {0, 1, 0, -1, 0}, my[5] = {1, 0, -1, 0, 0};
int N, M;
int Degree[30][30][30][30][2];
int Ans[30][30][30][30][2];
char Map[30][30];
int Qx, Qy, Ax, Ay;

struct Node
{
	int qx;
	int qy;
	int ax;
	int ay;
	int d;
};

int main ()
{
	while (scanf ("%d%d", &M, &N) == 2)
	{
		if (N == 0 && M == 0) break;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				scanf (" %c", &Map[i][j]);
				if (Map[i][j] == 'Q')
				{
					Qx = i;
					Qy = j;
				}
				if (Map[i][j] == 'A')
				{
					Ax = i;
					Ay = j;
				}
			}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				for (int k = 0; k < N; k++)
					for (int l = 0; l < M; l++)
					{
						Ans[i][j][k][l][0] = Ans[i][j][k][l][1] = 0;
						Degree[i][j][k][l][0] = Degree[i][j][k][l][1] = 0;
						for (int u = 0; u < 5; u++)
						{
							int nx = i + mx[u], ny = j + my[u];
							if (nx >= 0 && ny >= 0 && nx < N && ny < M && Map[nx][ny] != '#')
								Degree[i][j][k][l][0]++;
						}
						for (int u = 0; u < 5; u++)
						{
							int nx = k + mx[u], ny = l + my[u];
							if (nx >= 0 && ny >= 0 && nx < N && ny < M && Map[nx][ny] != '#')
								Degree[i][j][k][l][1]++;
						}
					}
		queue <Node> q;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (Map[i][j] != '#')
				{
					Ans[i][j][i][j][0] = -1;
					Ans[i][j][i][j][1] = 1;
					q.push ((Node) {i, j, i, j, 0});
					q.push ((Node) {i, j, i, j, 1}); 
				}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (Map[i][j] == 'E')
					for (int k = 0; k < N; k++)
						for (int l = 0; l < M; l++)
							if (Ans[i][j][k][l][0] == 0 && Map[k][l] != '#')
							{
								Ans[i][j][k][l][0] = 1;
								q.push ((Node) {i, j, k, l, 0});
							}
//		printf ("%d\n", Degree[0][0][0][1][0]);
		while (!q.empty ())
		{
			Node p = q.front ();
			int ans = Ans[p.qx][p.qy][p.ax][p.ay][p.d];
//			printf ("%d %d %d %d %d %d\n", p.qx, p.qy, p.ax, p.ay, p.d, ans);
			q.pop ();
			if (ans == -1)
			{
				if (p.d == 1)
				{
					for (int i = 0; i < 5; i++)
					{
						int nx = p.qx + mx[i], ny = p.qy + my[i];
						if (nx >= 0 && ny >= 0 && nx < N && ny < M && Ans[nx][ny][p.ax][p.ay][0] == 0 && Map[nx][ny] != '#')
						{
							Ans[nx][ny][p.ax][p.ay][0] = 1;
							q.push ((Node) {nx, ny, p.ax, p.ay, 0});
						}
					}
				}
				else
				{
					for (int i = 0; i < 5; i++)
					{
						int nx = p.ax + mx[i], ny = p.ay + my[i];
						if (nx >= 0 && ny >= 0 && nx < N && ny < M && Ans[p.qx][p.qy][nx][ny][1] == 0 && Map[nx][ny] != '#')
						{
							Ans[p.qx][p.qy][nx][ny][1] = 1;
							q.push ((Node) {p.qx, p.qy, nx, ny, 1});
						}

					}
				}
			}
			else
			{
				if (p.d == 1)
				{
					for (int i = 0; i < 5; i++)
					{
						int nx = p.qx + mx[i], ny = p.qy + my[i];
						if (nx >= 0 && ny >= 0 && nx < N && ny < M && Ans[nx][ny][p.ax][p.ay][0] == 0 && Map[nx][ny] != '#')
						{
							if (--Degree[nx][ny][p.ax][p.ay][0] == 0)
							{
								Ans[nx][ny][p.ax][p.ay][0] = -1;
								q.push ((Node) {nx, ny, p.ax, p.ay, 0});
							}
						}
					}
				}
				else
				{
					for (int i = 0; i < 5; i++)
					{
						int nx = p.ax + mx[i], ny = p.ay + my[i];
						if (nx >= 0 && ny >= 0 && nx < N && ny < M && Ans[p.qx][p.qy][nx][ny][1] == 0 && Map[nx][ny] != '#')
						{
							if (--Degree[p.qx][p.qy][nx][ny][1] == 0)
							{
								Ans[p.qx][p.qy][nx][ny][1] = -1;
								q.push ((Node) {p.qx, p.qy, nx, ny, 1});
							}
						}
					}
				}
			}
		}
		if (Ans[Qx][Qy][Ax][Ay][0] == 1)
			puts ("Queen can escape.");
		if (Ans[Qx][Qy][Ax][Ay][0] == -1)
			puts ("Army can catch Queen.");
		if (Ans[Qx][Qy][Ax][Ay][0] == 0)
			puts ("Queen can not escape and Army can not catch Queen.");
	}
}

