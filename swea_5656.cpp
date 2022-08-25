#include <iostream>
#include <vector>
using namespace std;

struct crd {
	int r;
	int c;
};

int bricks[15][12];
int tmpMap[15][12];
int answer = 2147483647;
int n, w, h;
vector<int> path;

int rdir[] = { -1,1,0,0 };
int cdir[] = { 0,0,-1,1 };

void boom(crd);
void dfs(int);

int main(int argc, char** argv) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		answer = 2147483647;
		cin >> n >> w >> h;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				cin >> bricks[i][j];
		dfs(0);
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}

void boom(crd now) {
	int range = tmpMap[now.r][now.c];
	tmpMap[now.r][now.c] = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < range; j++) {
			int nr = now.r + rdir[i] * j;
			int nc = now.c + cdir[i] * j;
			if (nr < 0 || nc < 0 || nr >= h || nc >= w) continue;
			if (tmpMap[nr][nc] == 0) continue;
			boom({ nr,nc });
		}
	}
}

void dfs(int now) {
	if (now >= n) {
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 12; j++)
				tmpMap[i][j] = bricks[i][j];

		for (int i = 0; i < n; i++) {
			int col = path[i];
			for (int row = 0; row < h; row++) {
				if (tmpMap[row][col]) {
					boom({ row,col });
					break;
				}
			}

			for (int c = 0; c < w; c++) {
				int lastZero = h - 1;
				for (int row = h - 1; row >= 0; row--) {
					if (tmpMap[row][c] != 0) {
						int tmp = tmpMap[row][c];
						tmpMap[row][c] = tmpMap[lastZero][c];
						tmpMap[lastZero][c] = tmp;
						lastZero--;
					}
				}
			}
		}

		int cnt = 0;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (tmpMap[i][j]) cnt++;
		answer = min(answer, cnt);
		return;
	}
	for (int i = 0; i < w; i++) {
		path.push_back(i);
		dfs(now + 1);
		path.pop_back();
	}
}