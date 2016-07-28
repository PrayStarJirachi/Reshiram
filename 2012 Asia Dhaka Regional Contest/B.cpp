#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int T;
int N;
char str[300];
int Stack[300], SC = 0;
bool Used[30];
int Degree[30];

int main ()
{
	scanf ("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf ("%s", str);
		N = strlen (str);
		for (int i = 0; i < 26; i++)
		{
			Used[i] = false;
			Degree[i] = 0;
		}
		Used[str[0] - 'A'] = true;
		Stack[0] = str[0] - 'A';
		SC = 1;
		for (int i = 1; i < N; i++)
		{
			if (!Used[str[i] - 'A'])
			{
				Degree[Stack[SC - 1]]++;
				Degree[str[i] - 'A']++;
				Used[str[i] - 'A'] = true;
				Stack[SC] = str[i] - 'A';
				SC++;
			}
			else
			{
				SC--;
			}
		}
		printf ("Case %d\n", t);
		for (int i = 0; i < 26; i++)
		{
//			printf ("%d\n", Degree[i]);
			if (Degree[i] > 0)
				printf ("%c = %d\n", i + 'A', Degree[i]);
		}
	}
}

