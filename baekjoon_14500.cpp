#include <iostream>
using namespace std;

int rdir[] = { -1,1,0,0 };
int cdir[] = { 0,0,-1,1 };

int n, m;
int numMap[500][500]{};
int visited[500][500]{};
int maxsum = 0;

int Tr[4][4] = {
	{0,0,0,1},{0,1,1,2},{0,1,1,1},{0,1,1,2}
};
int Tc[4][4] = {
	{0,1,2,1},{1,0,1,1},{1,0,1,2},{0,0,1,0}
};

void dfs(int r, int c, int t, int s) {
	if (t == 4) {
		if (maxsum < s) maxsum = s;
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nr = r + rdir[i];
		int nc = c + cdir[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (visited[nr][nc] == 1) continue;
		visited[nr][nc] = 1;
		dfs(nr, nc, t + 1, s + numMap[nr][nc]);
		visited[nr][nc] = 0;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> numMap[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = 1;
			dfs(i, j, 1, numMap[i][j]);
			visited[i][j] = 0;
		}
	}

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			for (int i = 0; i < 4; i++) {
				int tmpSum = 0;
				int flag = 1;
				for (int j = 0; j < 4; j++) {
					int nr = r + Tr[i][j];
					int nc = c + Tc[i][j];
					if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
						flag = 0;
						break;
					}
					tmpSum += numMap[nr][nc];
				}
				if (!flag) continue;
				if (maxsum < tmpSum) maxsum = tmpSum;
			}
		}
	}
	cout << maxsum;
	return 0;
}
