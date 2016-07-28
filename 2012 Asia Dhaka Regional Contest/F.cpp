#include <cstdio>
#include <cstring>

using namespace std;

int N, Q;
char Map[40][17][50];
int Co[40];
int Qn;
int Sum[17][50];

int ToNum (char c)
{
	if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
	return c - '0';
}

int main ()
{
	scanf ("%d%d", &N, &Q);
	for (int i = 0; i < N; i++)
	{
		char c;
		scanf (" %c", &c);
		Co[i] = ToNum (c);
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 17; j++)
			scanf ("%s", Map[Co[i]][j]);
	for (int i = 1; i <= Q; i++)
	{
		char str[100];
		scanf ("%s", str);
		Qn = strlen (str);
		for (int l = 0; l < 17; l++)
			for (int j = 0; j < 43; j++)
				Sum[l][j] = 0;
		for (int l = 0; l < Qn; l++)
		{
			for (int j = 0; j < 17; j++)
				for (int k = 0; k < 43; k++)
					if (Map[ToNum (str[l])][j][k] == '*') Sum[j][k]++;
		}
		printf ("Query %d: ", i);
		for (int l = 0; l < Qn; l++)
		{
			bool flag = false;
			for (int j = 0; j < 17; j++)
				for (int k = 0; k < 43; k++)
					if (Map[ToNum (str[l])][j][k] == '*' && Sum[j][k] == 1)
					{
						flag = true;
						break;
					}
			if (flag)
				printf ("Y");
			else
				printf ("N");
		}
		puts ("");
	}
}

