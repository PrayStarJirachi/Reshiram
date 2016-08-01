#include <cstdio>

using namespace std;

int DP[5][2000][2000] = {0};

int dp1 (int x, int y)
{
	if (DP[1][x][y] != -10) return DP[1][x][y];
	if (x == 1 && y == 1) return -1;
	int ans = -1;
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;
			int nx = x - i, ny = y - j;
			if (nx <= 0 || ny <= 0) continue;
			if (dp1 (nx, ny) == -1)
			{
				ans = 1;
				break;
			}
		}
	DP[1][x][y] = ans;
	return ans;
}

int dp3 (int x, int y)
{
	if (DP[3][x][y] != -10) return DP[3][x][y];
	if (x == 1 && y == 1) return -1;
	if (x - 2 > 0 && y - 1 > 0 && dp3 (x - 2, y - 1) == -1)
	{
		DP[3][x][y] = 1;
		return 1;
	}
	if (x - 1 > 0 && y - 2 > 0 && dp3 (x - 1, y - 2) == -1)
	{
		DP[3][x][y] = 1;
		return 1;
	}
	if (x - 2 > 0 && y - 1 > 0 && dp3 (x - 2, y - 1) == 0)
	{
		DP[3][x][y] = 0;
		return 0;
	}
	if (x - 1 > 0 && y - 2 > 0 && dp3 (x - 1, y - 2) == 0)
	{
		DP[3][x][y] = 0;
		return 0;
	}
	if ((x - 2 <= 0 || y - 1 <= 0) && (x - 1 <= 0 || y - 2 <= 0))
	{
		DP[3][x][y] = 0;
		return 0;
	}
	DP[3][x][y] = -1;
	return -1;
}

char Tochar (int a)
{
	if (a == 1) return 'B';
	if (a == 0) return 'D';
	if (a == -1) return 'G';
	return 'U';
}

int main ()
{
	for (int t = 1; t <= 4; t++)
		for (int i = 1; i <= 1000; i++)
			for (int j = 1; j <= 1000; j++)
				DP[t][i][j] = -10;
	for (int i = 1; i <= 1000; i++)
	{
		int x = i, y = 1;
		while (x >= 1 & y <= 1000)
		{
			if (DP[4][x][y] == -10)
			{
				DP[4][x][y] = -1;
				for (int i = x + 1; i <= 1000; i++)
					DP[4][i][y] = 1;
				for (int i = y + 1; i <= 1000; i++)
					DP[4][x][i] = 1;
				for (int i = 1; x + i <= 1000 && y + i <= 1000; i++)
					DP[4][x + i][y + i] = 1;
			}
			x--;
			y++;
		}
	}
	for (int i = 1002; i <= 2000; i++)
	{
		int x = 1000, y = i - x;
		while (x >= 1 && y <= 1000)
		{
			if (DP[4][x][y] == -10)
			{
				DP[4][x][y] = -1;
				for (int i = x + 1; i <= 1000; i++)
					DP[4][i][y] = 1;
				for (int i = y + 1; i <= 1000; i++)
					DP[4][x][i] = 1;
				for (int i = 1; x + i <= 1000 && y + i <= 1000; i++)
					DP[4][x + i][y + i] = 1;
			}
			x--;
			y++;
		}
	}
	int T;
	scanf ("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		int tp, a, b;
		scanf ("%d%d%d", &tp, &a, &b);
		if (tp == 2)
		{
			if (a == b)
				printf ("G\n");
			else
				printf ("B\n"); 
		}
		else
		{
			if (tp == 1)
				printf ("%c\n", Tochar (dp1 (a, b)));
			if (tp == 3)
				printf ("%c\n", Tochar (dp3 (a, b)));
			if (tp == 4)
				printf ("%c\n", Tochar (DP[tp][a][b]));
		}
	}
}

