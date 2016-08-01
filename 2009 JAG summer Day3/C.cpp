#include <bits/stdc++.h>

const int MAXN = 100001;
const long double EPS = 1e-6;

int dcmp(const long double &x) {
	return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

struct Point{
	long double x, y;
	Point() : x(0), y(0) {}
	Point(const long double &x, const long double &y) : x(x), y(y) {}

	Point operator +(const Point &rhs)const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator -(const Point &rhs)const {
		return Point(x - rhs.x, y - rhs.y);
	}
	Point operator *(const long double &rhs)const {
		return Point(x * rhs, y * rhs);
	}
	Point operator /(const long double &rhs)const {
		return Point(x / rhs, y / rhs);
	}
	long double length()const {
		return sqrt(x * x + y * y);
	}
	Point unitize()const {
		Point ret = *this;
		return ret / this -> length();
	}
	Point normalize()const {
		return Point(-y, x);
	}
	bool operator ==(const Point &rhs)const {
		return dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) == 0;
	}
	bool operator !=(const Point &rhs)const {
		return dcmp(x - rhs.x) != 0 || dcmp(y - rhs.y) != 0;
	}
	bool operator <(const Point &rhs)const {
		return dcmp(x - rhs.x) < 0 || (dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) < 0);
	}
	void print()const {
		printf("%.10f %.10f\n", (double)x, (double)y);
	}
	void read() {
		double tmpx, tmpy;
		scanf("%lf%lf", &tmpx, &tmpy);
		x = tmpx;
		y = tmpy;
	}

};

long double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

long double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

struct Line{
	Point a, b;
	Line() {}
	Line(const Point &a, const Point &b) : a(a), b(b) {}
	void read() {
		a.read();
		b.read();
	}
	bool isPoint()const {
		return a == b;
	}
}l[MAXN];

typedef std::vector<Line> Set;

int n;

Point getIntersection(const Line &l, const Line &r) {
	long double s1 = det(l.b - l.a, r.a - l.a);
	long double s2 = det(l.b - l.a, r.b - l.a);
	return (r.a * s2 - r.b * s1) / (s2 - s1);
}

std::pair<bool, Line> getUnion(const Line &l, const Line &r) {
	if (dcmp(det(l.a - r.a, r.b - r.a)) == 0 && dcmp(det(l.b - r.a, r.b - r.a)) == 0) {
		return std::make_pair(true, l);
	} else if (l.a != l.b && r.a != r.b && dcmp(det(l.b - l.a, r.b - r.a)) != 0) {
		Point v = getIntersection(l, r);
		return std::make_pair(true, Line(v, v));
	} else {
		return std::make_pair(false, Line());
	}
}

Set getIntersection(const Set &a, const Set &b) {
	Set ret;
	for (int i = 0; i < (int)a.size(); i++)
		for (int j = 0; j < (int)b.size(); j++) {
			std::pair<bool, Line> tmp = getUnion(a[i], b[j]);
			if (tmp.first) ret.push_back(tmp.second);
		}
	return ret;
}

Point getVector(const Point &a, const Point &b) {
	return (a.unitize() - b.unitize()) * 10000;
}

Set getLine(const Line &l, const Line &r) {
	Set ret;
	if (dcmp(det(l.a - l.b, r.a - r.b)) == 0) {
		Line tmp;
		tmp.a = (l.a + r.a) / 2.0;
		tmp.b = tmp.a + l.b - l.a;
		ret.push_back(tmp);
		return ret;
	} else {
		Line ret1;
		ret1.a = getIntersection(l, r);
		ret1.b = ret1.a + getVector(l.b - l.a, r.b - r.a);
		Line ret2;
		ret2.a = getIntersection(l, r);
		ret2.b = ret2.a + getVector(l.b - l.a, r.b - r.a).normalize();
		ret.push_back(ret1);
		ret.push_back(ret2);
		return ret;
	}
}

int main() {
	freopen("C.in", "r", stdin);
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++) {
			l[i].read();
		}
		if (n == 1) {
			puts("Many");
			continue;
		}
		Set answer = getLine(l[1], l[2]);
		for (int i = 3; i <= n; i++) {
				
			answer = getIntersection(answer, getLine(l[i], l[1]));
		}
		if (answer.empty()) {
			puts("None");	
		} else {
			if (!answer[0].isPoint()) {
				puts("Many");
			} else {
				Point a = answer[0].a;
				bool flag = true;
				for (int i = 1; i < (int)answer.size(); i++) {
					if (!answer[i].isPoint() || answer[i].a != a) {
						flag = false;
						break;
					}
				}
				if (flag) a.print();
				else puts("Many");
			}
		}
	}
	return 0;
}
