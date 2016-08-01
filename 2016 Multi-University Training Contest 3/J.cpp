#include <cstdio>
#include <algorithm>
#include <cmath>

const double EPS = 1e-8;

int T;

int dcmp(const double &x) {
	return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

int main() {
	double a, v1, v2;
	while (scanf("%lf%lf%lf", &a, &v1, &v2) == 3) {
		if (dcmp(a) == 0) puts("0.000000000000000");
		else{
			if (dcmp(v1 - v2) <= 0) puts("Infinity");
			else{
				double answer = a * v1 / (v1 * v1 - v2 * v2);
				printf("%.10f\n", answer);
			}
		}
	}
	return 0;
}
