#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;
const int INF = ~0u >> 2;

struct Edge{
	int node, next, flow, cost, opp;
}e[MAXM];

int T, n, m, t, pre[MAXN], h[MAXN], cur[MAXN], stdAns[MAXN];
std::vector<int> srcPos[26];

void addEdge(int x, int y, int f, int c) {
	t++; e[t] = (Edge){y, h[x], f, c, t + 1}; h[x] = t;
	t++; e[t] = (Edge){x, h[y], 0, -c, t - 1}; h[y] = t;
}

bool spfa(int s, int t, int n) {
	static int q[MAXN], d[MAXN];
	static bool v[MAXN];
	std::fill(d + 1, d + n + 1, -INF);
	std::fill(v + 1, v + n + 1, false);
	int left = 0, right = 0;
	v[q[++right] = s] = true;
	d[s] = 0; pre[s] = 0;
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (e[i].flow && d[e[i].node] < d[q[left]] + e[i].cost) {
				d[e[i].node] = d[q[left]] + e[i].cost;
				pre[e[i].node] = q[left];
				cur[e[i].node] = i;
				if (!v[e[i].node]) {
					v[q[++right] = e[i].node] = true;
				}
			}
		}
		v[q[left]] = false;
	}
	return d[t] > -INF;
}

int MCMF(int s, int t, int n) {
	int ret = 0;
	while (spfa(s, t, n)) {
		int dflow = INF;
		for (int i = t; i != s; i = pre[i]) dflow = std::min(dflow, e[cur[i]].flow);
		for (int i = t; i != s; i = pre[i]) {
			e[cur[i]].flow -= dflow;
			e[e[cur[i]].opp].flow += dflow;
			ret += dflow * e[cur[i]].cost;
		}
	}
	return ret;
}

int main() {
	freopen("J.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%*d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			char op[20];
			scanf("%s", op);
			stdAns[i] = op[0] - 'A';
		}
		for (int base = 1; base <= m; base++) {
			for (int i = 0; i < 26; i++) srcPos[i].clear();
			for (int i = 1; i <= n; i++) {
				char op[20];
				scanf("%s", op);
				srcPos[op[0] - 'A'].push_back(i);
			}
			std::fill(h + 1, h + 2 * 26 + 2 + 1, t = 0);
			for (int i = 1; i <= 26; i++) {
				addEdge(2 * 26 + 1, i, 1, 0);
				addEdge(26 + i, 2 * 26 + 2, 1, 0);
			}
			for (int i = 0; i < 26; i++) {
				if (srcPos[i].empty()) continue;
				for (int j = 0; j < 26; j++) {
					int value = 0;
					for (int k = 0; k < (int)srcPos[i].size(); k++)
						value += (stdAns[srcPos[i][k]] == j);
					addEdge(i + 1, 26 + j + 1, 1, value);
				}
			}
			int answer = MCMF(2 * 26 + 1, 2 * 26 + 2, 2 * 26 + 2);
			printf("%.4f\n", 1.0 * answer / n);
		}
	}
	return 0;
}
