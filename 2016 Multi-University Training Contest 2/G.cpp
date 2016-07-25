#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXN = 2001;
const int MAXM = 4000001;
const int INF = 1ll << 25;

struct KMSolver{
	static const int MAXN = 1001;

	struct KMState {
		int lx[MAXN], ly[MAXN], match[MAXN], way[MAXN];
		void init(int n) {
			for (int i = 1; i <= n; i ++) {
				match[i] = 0;
				lx[i] = 0;
				ly[i] = 0;
				way[i] = 0;
			}
		}
	}state;

	int w[MAXN][MAXN], slack[MAXN];
	bool used[MAXN];

	void init(int n) {
		state.init(n);
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				w[i][j] = 0;
			}
		}
	}
	void hungary(int x, int n) {
		state.match[0] = x;
		int j0 = 0;
		for (int j = 0; j <= n; j ++) {
			slack[j] = INF;
			used[j] = false;
		}
		do {
			used[j0] = true;
			int i0 = state.match[j0], delta = INF, j1;
			for (int j = 1; j <= n; j ++) {
				if (used[j] == false) {
					int cur = w[i0][j] - state.lx[i0] - state.ly[j];
					if (cur < slack[j]) {
						slack[j] = cur;
						state.way[j] = j0;
					}
					if (slack[j] < delta) {
						delta = slack[j];
						j1 = j;
					}
				}
			}
			for (int j = 0; j <= n; j ++) {
				if (used[j]) {
					state.lx[state.match[j]] += delta;
					state.ly[j] -= delta;
				} else {
					slack[j] -= delta;
				}
			}
			j0 = j1;
		} while (state.match[j0] != 0);
		do {
			int j1 = state.way[j0];
			state.match[j0] = state.match[j1];
			j0 = j1;
		} while (j0);
	}
	std::pair<int, std::vector<std::pair<int, int> > > solve(int n) {
		for (int i = 1; i <= n; i++) {
			hungary(i, n);
		}
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			if (state.match[i] > 0) {
				ret += w[state.match[i]][i];
			}
		}
		std::vector<std::pair<int, int> > way;
		for (int i = 1; i <= n; i++) {
			way.push_back(std::make_pair(state.match[i], i));
		}
		return std::make_pair(ret, way);
	}
}KM;

int T, n, m, d[MAXN][MAXN], pre[MAXN][MAXN], color[MAXN], q[MAXN];
char raw[MAXN], storage[MAXN];
std::vector<int> g[MAXN];

void bfs(int x, int n, int *d, int *pre) {
	std::fill(d + 1, d + n + 1, INF);
	int left = 0, right = 0;
	q[++right] = x;
	d[x] = 0; pre[x] = 0;
	while (left < right) {
		left++;
		for (int i = 0; i < (int)g[q[left]].size(); i++) {
			int now = g[q[left]][i];
			if (d[now] < INF) continue;
			d[now] = d[q[left]] + 1;
			pre[now] = q[left];
			q[++right] = now;
		}
	}
}

void addConstructedPath(const std::pair<int, int> &pair, std::vector<std::pair<int, int> > &path) {
	std::vector<int> container;
	for (int i = pair.second; i != pair.first; i = pre[pair.first][i]) {
		container.push_back(i);
	}
	container.push_back(pair.first);
	std::reverse(container.begin(), container.end());
	for (int i = 0; i + 1 < (int)container.size();) {
		int j = i;
		while (j + 1 < (int)container.size() && raw[container[j]] == raw[container[i]]) {
			j++;
		}
		for (int k = j - 1; k >= i; k--) {
			path.push_back(std::make_pair(container[k + 1], container[k]));
			std::swap(raw[container[k + 1]], raw[container[k]]);
		}
		i = j;
	}
}

int main() {
	freopen("G.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d", &n, &m);
		scanf("%s", raw + 1);
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		for (int i = 1; i <= n; i++) {
			std::sort(g[i].begin(), g[i].end());
			g[i].erase(std::unique(g[i].begin(), g[i].end()), g[i].end());
		}

		for (int i = 1; i <= n; i++) {
			bfs(i, n, d[i], pre[i]);
		}

		std::vector<std::pair<int, int> > answer;
		std::fill(color + 1, color + n + 1, 0);
		bool flag = true;
		for (int base = 1; base <= n; base++) {
			if (color[base]) continue;
			static int q[MAXN];
			int left = 0, right = 0;
			color[q[++right] = base] = 1;
			while (left < right) {
				left++;
				for (int i = 0; i < (int)g[q[left]].size(); i++) {
					int now = g[q[left]][i];
					if (color[now]) continue;
					color[q[++right] = now] = 3 - color[q[left]];
				}
			}
			for (int i = 1; i <= right && flag; i++) {
				for (int j = 0; j < (int)g[q[i]].size(); j++) {
					if (color[g[q[i]][j]] + color[q[i]] != 3) {
						flag = false;
						break;
					}
				}
			}
			if (!flag) break;
			std::vector<std::pair<int, int> > tmp;
			bool existAnswer = false;
			for (int defaultBlack = 1; defaultBlack <= 2; defaultBlack++) {
				static int colA[MAXN], colB[MAXN], oA[MAXN], oB[MAXN];
				int cntBlackA = 0, cntBlackB = 0;
				for (int i = 1; i <= right; i++) {
					if (raw[q[i]] == '1' && color[q[i]] != defaultBlack) {
						oA[colA[q[i]] = ++cntBlackA] = q[i];
					}
					if (raw[q[i]] != '1' && color[q[i]] == defaultBlack) {
						oB[colB[q[i]] = ++cntBlackB] = q[i];
					}
				}
				if (cntBlackA == cntBlackB) {
					KM.init(cntBlackA);
					for (int i = 1; i <= cntBlackA; i++)
						for (int j = 1; j <= cntBlackB; j++)
							KM.w[i][j] = d[oA[i]][oB[j]];
					std::pair<int, std::vector<std::pair<int, int> > > way = KM.solve(cntBlackA);
					if (way.first < INF) {
						std::vector<std::pair<int, int> > buffer;
						memcpy(storage, raw, sizeof raw);
						for (int i = 0; i < (int)way.second.size(); i++) {
							std::pair<int, int> now = way.second[i];
							now.first = oA[now.first];
							now.second = oB[now.second];
							addConstructedPath(now, buffer);
						}
						memcpy(raw, storage, sizeof raw);
						if (!existAnswer || buffer.size() < tmp.size()) {
							tmp = buffer;
						}
						existAnswer = true;
					}
				}
			}
			if (!existAnswer) {
				flag = false;
				break;
			}
			for (int i = 0; i < (int)tmp.size(); i++) {
				answer.push_back(tmp[i]);
			}
		}

		if (!flag) {
			puts("-1");
			continue;
		}
		printf("%d\n", (int)answer.size());
		for (int i = 0; i < (int)answer.size(); i++) {
			printf("%d %d\n", answer[i].second, answer[i].first);
		}
	}
	return 0;
}
