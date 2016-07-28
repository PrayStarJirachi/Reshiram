#include <cstdio>
#include <utility>

using namespace std;

int T, N;
int A, B;
bool Used[500];

struct Node
{
	double k;
	double b;
	int a;
};

Node R (int x)
{
	if (x == 0)
		return ((Node) {0, 0, -1});
	if (Used[x])
		return ((Node) {1, 0, x});
	Used[x] = true;
	Node n = R ((2 * x) % N);
	if (n.a == x)
		return ((Node) {0, (2 + n.b) / (2 - n.k), -1});
	return ((Node) {n.k / 2, n.b / 2 + 1, n.a});
}

Node P (int x)
{
	if (x == 0)
		return ((Node) {0, 0, -1});
	if (Used[x])
		return ((Node) {1, 0, x});
	if (x == N)
		return ((Node) {0, 1, -1});
	if (x * 2 == N)
		return ((Node) {0, 0.5, -1});
	Used[x] = true;
	if (x * 2 < N)
	{
		Node n = P (x * 2);
		if (n.a == x)
			return ((Node) {0, (n.b / 2) / (1.0 - n.k / 2), -1});
		return ((Node) {n.k / 2, n.b / 2, n.a});
	}
	Node n = P (x * 2 - N);
	if (n.a == x)
		return ((Node) {0, (n.b + 1) / (2 - n.k), -1});
	return ((Node) {n.k / 2, n.b / 2 + 0.5, n.a});
}

int main ()
{
	scanf ("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf ("%d%d", &A, &B);
		N = A + B;
		for (int i = 0; i <= N; i++)
			Used[i] = false;
		Node r = R (A);
		for (int i = 0; i <= N; i++)
			Used[i] = false;
		Node p = P (A);
		printf ("Case %d: %.6f %.6f\n", t, r.b, p.b);
	}
}

