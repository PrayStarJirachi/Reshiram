#include <cstdio>

#define llong long long

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

using namespace std;

llong T, N, K;
llong M[60000];
llong dmg[60000], dec[60000], det[60000];
llong chg[60000];

__inline llong udiv (llong a, llong b)
{
	return a / b + ((a % b == 0) ? 0 : 1);
}

bool Valid (llong p)
{
	llong nec = udiv (M[N - 1], p);
//	printf ("nec = %lld, K = %lld\n", nec, K);
	llong k = K;
	llong f = 0, fdmg = 0;
	for (f = 0; f <= 60000; f++)
		if (p - f * f <= 0) break;
	fdmg = p - f * f;
	for (int i = 0; i < N; i++)
		chg[i] = 0;
	dmg[N - 1] = nec * p;
	dec[N - 1] = -nec;
	det[N - 1] = -2 * nec;
	k -= nec;
	if (k < 0) return false;
	if (N - 1 - f >= 0)
		chg[N - 1 - f] += nec;
	for (llong i = N - 2; i >= 0; i--)
	{
		llong odmg = dmg[i + 1] + dec[i + 1] - fdmg * chg[i];
		llong odec = dec[i + 1] + det[i + 1] + (2 * f + 1) * chg[i];
		llong odet = det[i + 1] + 2 * chg[i];
		if (M[i] > odmg)
			nec = udiv (M[i] - odmg, p);
		else
			nec = 0;
		k -= nec;
		if (k < 0) return false;
		if (i - f >= 0)
			chg[i - f] += nec;
		dmg[i] = odmg + nec * p;
		dec[i] = odec - nec;
		det[i] = odet - 2 * nec;
	}
	return true;
}

int main ()
{
	scanf (LL, &T);
	for (int t = 0; t < T; t++)
	{
		scanf (LL LL, &N, &K);
		for (int i = 0; i < N; i++)
			scanf (LL, &M[i]), M[i]++;
		llong l = 1, r = 5000000000LL;
		while (l < r) {
			llong m = l + r >> 1;
			if (Valid(m)) r = m;
			else l = m + 1;
		}
		printf (LL "\n", l);
	}
}

