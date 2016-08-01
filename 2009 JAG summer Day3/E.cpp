#include <cstdio>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int Trans[6][8] = 
{
	{1, 2, 3, 4, 5, 6, 7, 8}, 
	{1, 5, 6, 2, 4, 8, 7, 3},
	{5, 8, 7, 6, 1, 4, 3, 2},
	{4, 3, 7, 8, 1, 2, 6, 5},
	{5, 1, 4, 8, 6, 2, 3, 7},
	{7, 3, 2, 6, 8, 4, 1, 5}
};

set <vector <string> > s;

bool Valid (vector <string> &S)
{
	vector <string> T;
	T.resize (8);
	for (int t = 0; t < 6; t++)
		for (int r = 0; r < 4; r++)
		{
			for (int i = 0; i < 4; i++)
			{
				 T[i] = S[Trans[t][(r + i) % 4] - 1];
				 T[i + 4] = S[Trans[t][(r + i) % 4 + 4] - 1];
			}
			if (s.find (T) != s.end ()) return false;
		}
	return true;
}

int main ()
{
	ios::sync_with_stdio (false);
	cin.tie (0);
	vector <string> Ori;
	Ori.resize (8);
	vector <string> S;
	S.resize (8);
	while (cin >> Ori[0])
	{
		for (int i = 1; i < 8; i++)
			cin >> Ori[i];
		int Pre[8] = {0, 1, 2, 3, 4, 5, 6, 7};
		s.clear ();
		for (int i = 0; i < 42000; i++)
		{
			for (int j = 0; j < 8; j++)
				S[j] = Ori[Pre[j]];
			if (Valid (S))
				s.insert (S);
			next_permutation (Pre, &Pre[8]);
		}
		printf ("%d\n", (int) s.size ());
	}
}

