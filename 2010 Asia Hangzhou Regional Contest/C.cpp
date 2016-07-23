#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

const int MAXB = 1100001;

struct Tuple{
	int x, y, z;
	bool operator <(const Tuple &rhs)const {
		if (x < rhs.x) return true;
		if (x > rhs.x) return false;
		if (y < rhs.y) return true;
		if (y > rhs.y) return false;
		return z < rhs.z;
	}
	bool operator ==(const Tuple &rhs)const {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}
}block[MAXB];

int T, n, m;

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		
		int tot = 0;
		for (int i = 1; i <= m; i++) {
			std::string buffer;
			std::cin >> buffer;
			char o1 = buffer[0];
			int d1 = atoi(buffer.substr(buffer.find('=') + 1, buffer.find(',') - buffer.find('=') - 1).c_str());
			buffer.erase(0, buffer.find(',') + 1);
			char o2 = buffer[0];
			int d2 = atoi(buffer.substr(buffer.find('=') + 1, buffer.find(',') - buffer.find('=') - 1).c_str());
			if (o1 > o2) {
				std::swap(o1, o2);
				std::swap(d1, d2);
			}
			if (d1 < 1 || d1 > n || d2 < 1 || d2 > n) continue;
			if (o1 == 'X' && o2 == 'Y') {
				for (int z = 1; z <= n; z++) {
					block[++tot] = (Tuple){d1, d2, z};
				}
			}
			if (o1 == 'Y' && o2 == 'Z') {
				for (int x = 1; x <= n; x++) {
					block[++tot] = (Tuple){x, d1, d2};
				}
			}
			if (o1 == 'X' && o2 == 'Z') {
				for (int y = 1; y <= n; y++) {
					block[++tot] = (Tuple){d1, y, d2};
				}
			}
		}
		
		std::sort(block + 1, block + tot + 1);
		tot = std::unique(block + 1, block + tot + 1) - block - 1;
		printf("%d\n", tot);
	}
	return 0;
}
