#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 15;
const int MAXM = 21;
const char NAME[2][10] = {"white", "black"};

int n, map[MAXM][MAXM];

bool checkWin(int x, int y, int c) {
	int tL = 1, tR = 1, tU = 1, tD = 1, tLU = 1, tRU = 1, tLD = 1, tRD = 1;
	for (int i = x - 1; i >= 0 && map[i][y] == c; i--) tU++;
	for (int i = x + 1; i < N && map[i][y] == c; i++) tD++;
	if (tU + tD - 1 >= 5) return true;

	for (int i = y - 1; i >= 0 && map[x][i] == c; i--) tL++;
	for (int i = y + 1; i < N && map[x][i] == c; i++) tR++;
	if (tL + tR - 1 >= 5) return true;

	for (int i = 1; x - i >= 0 && y - i >= 0 && map[x - i][y - i] == c; i++) tLU++;
	for (int i = 1; x + i < N && y + i < N && map[x + i][y + i] == c; i++) tRD++;
	if (tLU + tRD - 1 >= 5) return true;

	for (int i = 1; x - i >= 0 && y + i < N && map[x - i][y + i] == c; i++) tRU++;
	for (int i = 1; x + i < N && y - i >= 0 && map[x + i][y - i] == c; i++) tLD++;
	if (tRU + tLD - 1 >= 5) return true;

	return false;
}

std::pair<bool, std::pair<int, int> > checkOne(const std::vector<std::pair<int, int> > &free, const int &firstMove) {
	for (int i = 0; i < (int)free.size(); i++) {
		std::pair<int, int> pos = free[i];
		if (checkWin(pos.first, pos.second, firstMove)) {
			return std::make_pair(true, pos);
		}
	}
	return std::make_pair(false, std::make_pair(-1, -1));
}

bool checkTwo(const std::vector<std::pair<int, int> > &free, const int &firstMove) {
	for (int i = 0; i < (int)free.size(); i++) {
		map[free[i].first][free[i].second] = firstMove;
		bool flag = false;
		for (int j = 0; j < (int)free.size(); j++) {
			if (i == j) continue;
			if (checkWin(free[j].first, free[j].second, firstMove ^ 1)) {
				flag = true;
				break;
			}
		}
		map[free[i].first][free[i].second] = -1;
		if (!flag) {
			return false;
		}
	}
	return true;
}

std::pair<bool, std::pair<int, int> > checkThree(const std::vector<std::pair<int, int> > &free, const int &firstMove) {
	for (int i = 0; i < (int)free.size(); i++) {

		map[free[i].first][free[i].second] = firstMove;

		bool canwin = false;
		for (int j = 0; j < (int)free.size(); j++) {
			if (i == j) continue;
			if (checkWin(free[j].first, free[j].second, firstMove ^ 1)) {
				canwin = true;
				break;
			}
		}
		if (canwin) {
			map[free[i].first][free[i].second] = -1;
			continue;
		}

		bool notwin = false;
		for (int j = 0; j < (int)free.size(); j++) {
			if (i == j) continue;

			map[free[j].first][free[j].second] = firstMove ^ 1;

			bool flag = false;
			for (int k = 0; k < (int)free.size(); k++) {
				if (i == k || j == k) continue;
				if (checkWin(free[k].first, free[k].second, firstMove)) {
					flag = true;
					break;
				}
			}

			map[free[j].first][free[j].second] = -1;
			if (!flag) {
				notwin = true;
				break;
			}
		}

		map[free[i].first][free[i].second] = -1;
		if (!notwin) {
			return std::make_pair(true, free[i]);
		}
	}
	return std::make_pair(false, std::make_pair(-1, -1));
}

int main() {
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;

		memset(map, -1, sizeof map);

		int nBlack = 0, nWhite = 0;
		for (int i = 0; i < n; i++) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			map[x][y] = c;
			if (c == 0) nWhite++;
			else nBlack++;
		}

		std::vector<std::pair<int, int> > free;
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (map[i][j] == -1) {
					free.push_back(std::make_pair(i, j));
				}

		int firstMove;
		if (nBlack == nWhite) {
			firstMove = 1;
		} else if (nBlack == nWhite + 1) {
			firstMove = 0;
		} else {
			puts("Invalid.");
			continue;
		}
		
		std::pair<bool, std::pair<int, int> > ret;

		ret = checkOne(free, firstMove);
		if (ret.first) {
			printf("Place %s at (%d,%d) to win in 1 move.\n", NAME[firstMove], ret.second.first, ret.second.second);
			continue;
		}

		if (checkTwo(free, firstMove)) {
			printf("Lose in 2 moves.\n");
			continue;
		}

		ret = checkThree(free, firstMove);
		if (ret.first) {
			printf("Place %s at (%d,%d) to win in 3 moves.\n", NAME[firstMove], ret.second.first, ret.second.second);
			continue;
		}
		
		puts("Cannot win in 3 moves.");
	}
	return 0;
}
