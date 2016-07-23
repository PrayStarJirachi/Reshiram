#include <cmath>
#include <cstdio>
#include <algorithm>

const double EPS = 0;
const int MAXN = 200001;

int dcmp(const double &x) {
	return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

struct Point{
	double x, y;
	Point() : x(0), y(0) {}
	Point(const double &x, const double &y) : x(x), y(y) {}
	
	Point operator +(const Point &rhs)const {
		return Point(x + rhs.x, y + rhs.y);
	}
	
	Point operator -(const Point &rhs)const {
		return Point(x - rhs.x, y - rhs.y);
	}
	
	Point operator *(const double &rhs)const {
		return Point(x * rhs, y * rhs);
	}
	
	Point operator /(const double &rhs)const {
		return Point(x / rhs, y / rhs);
	}
	
	double sqrlen()const {
		return x * x + y * y;
	}
	
	void read() {
		scanf("%lf%lf", &x, &y);
	}
}c[MAXN], p[MAXN];

int T, n;

double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

bool pairCmp(const Point &a, const Point &b) {
	if (dcmp(a.x - b.x) < 0) return true;
	if (dcmp(a.x - b.x) > 0) return false;
	return dcmp(a.y - b.y) < 0;
}

int getConvexHull(int n, Point *P, Point *C) {
	std::sort(P, P + n, pairCmp);
	int top = 0;
	for (int i = 0; i < n; i++) {
		while (top >= 2 && dcmp(det(C[top - 1] - C[top - 2], P[i] - C[top - 2])) <= 0) top--;
		C[top++] = P[i];
	}
	int lasttop = top;
	for (int i = n - 1; i >= 0; i--) {
		while (top > lasttop && dcmp(det(C[top - 1] - C[top - 2], P[i] - C[top - 2])) <= 0) top--;
		C[top++] = P[i];
	}
	return top;
}

Point getGravityPoint(int n, Point *p) {
	double area = 0;
	Point ret(0, 0);
	for (int i = 1; i + 1 < n; i++) area += det(p[i] - p[0], p[(i + 1) % n] - p[0]);
	for (int i = 1; i + 1 < n; i++) {
		ret = ret + (p[0] + p[i] + p[(i + 1) % n]) / 3.0 * det(p[i] - p[0], p[(i + 1) % n] - p[0]);
	}
	ret = ret / area;
	return ret;
}

int main() {
	freopen("F.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) p[i].read();
		Point g = getGravityPoint(n, p);
		int tot = getConvexHull(n, p, c);
		int answer = 0;
		for (int i = 0; i < tot; i++) {
			Point vector = c[(i + 1) % tot] - c[i];
			double rate = dot(g - c[i], vector);
			if (dcmp(rate) > 0 && dcmp(rate - vector.sqrlen()) < 0) {
				answer++;
			}
		}
		printf("%d\n", answer);
	}
	return 0;
}
