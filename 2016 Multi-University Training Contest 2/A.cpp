#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 110001;

int T, n;
long long 	w[MAXN];

int main() {
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf(LL, w + i);
		long long p1 = 0, p2 = 0, q = n;
		for (int i = 1; i <= n; i++) {
			p1 += std::abs(w[i]);
		}
		p1 = p1 * p1;
		long long p = -p1;
		for (int i = 1; i <= n; i++) {
			p += 1ll * n * w[i] * w[i];
		}
		long long g = std::__gcd(p, q);
		p /= g;
		q /= g;
		if (q < 0) {
			p = -p;
			q = -q;
		}
		printf(LL "/" LL "\n", p, q);
	}
	return 0;
}
