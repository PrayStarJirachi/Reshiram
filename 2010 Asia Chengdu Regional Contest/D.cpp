#include <cmath>
#include <cstdio>
#include <algorithm>

const double EPS = 1e-10;

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
	Point operator -()const {
		return Point(-x, -y);
	}
	double length()const {
		return sqrt(x * x + y * y);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
}p[3];

struct Line{
	Point a, b;
	Line() {}
	Line(const Point &a, const Point &b) : a(a), b(b) {}
}r;

int T;
double rate;

double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

Point getIntersection(const Line &l, const Line &r) {
	double sA = det(r.a - l.a, l.b - l.a);
	double sB = det(l.b - l.a, r.b - l.a);
	return r.a + (r.b - r.a) * (sA / (sA + sB));
}

bool isColinear(const Line &l, const Line &r) {
	return dcmp(det(l.b - l.a, r.b - r.a)) == 0;
}

Point rotate(const Point &v, const double &theta) {
	Point ret;
	ret.x = v.x * cos(theta) - v.y * sin(theta);
	ret.y = v.x * sin(theta) + v.y * cos(theta);
	return ret;
}

double getAlpha(const Point &a, const Point &b) {
	return acos(dot(a, b) / a.length() / b.length());
}

std::pair<bool, Line> getMain(const Line &raser, const double &rate) {
	int pos = -1;
	double answer = 0;
	for (int i = 0; i < 3; i++) {
		if (isColinear(raser, Line(p[i], p[(i + 1) % 3]))) continue;
		Point c = getIntersection(raser, Line(p[i], p[(i + 1) % 3]));
		if (dcmp(dot(c - p[i], c - p[(i + 1) % 3])) > 0) continue;
		if (dcmp(dot(c - raser.a, raser.b - raser.a)) <= 0) continue;
		if (pos == -1 || (answer > dot(c - raser.a, raser.b - raser.a))) {
			pos = i;
			answer = dot(c - raser.a, raser.b - raser.a);
		}
	}
	if (pos == -1) return std::make_pair(false, raser);
	Point c = getIntersection(raser, Line(p[pos], p[(pos + 1) % 3]));
	Point d = p[(pos + 1) % 3] - p[pos];
	Point wf = Point(-d.y, d.x);
	Line v(c, c + wf);
	if (dcmp(dot(raser.b - raser.a, d)) == 0) return std::make_pair(true, Line(v.a, v.a - wf));
	int face = dcmp(det(wf, raser.b - raser.a));
	face = -face;
	double alpha = getAlpha(raser.b - raser.a, wf);
	double beta = asin(sin(alpha) / rate);
	Point gxx = rotate(-wf, beta * face);
	return std::make_pair(true, Line(c, c + gxx));
}

double fix(const double &x) {
	if (fabs(x) < EPS) return 0;
	else return x;
}

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		r.a.read();
		r.b.read();
		for (int i = 0; i < 3; i++) p[i].read();
		if (dcmp(det(p[0], p[1]) + det(p[1], p[2]) + det(p[2], p[0])) > 0) {
			std::reverse(p, p + 3);
		}
		for (int i = 0; i < 3; i++)
			printf("(%.2f, %.2f)\n", p[i].x, p[i].y);
		scanf("%lf", &rate);
		for (int cnt = 0; cnt < 2; cnt++) {
			std::pair<bool, Line> ret;
			if (cnt == 0) ret = getMain(r, rate);
			else ret = getMain(r, 1 / rate);
			if (!ret.first) break;
			r = ret.second;
		}
		if (isColinear(r, Line(Point(0, 0), Point(1, 0)))) {
			puts("Error");
			continue;
		}
		Point answer = getIntersection(r, Line(Point(0, 0), Point(1, 0)));
		if (dcmp(dot(answer - r.a, r.b - r.a)) > 0) {
			printf("%.3f\n", fix(answer.x));
		} else {
			puts("Error");
		}
	}
	return 0;
}
