#include <iostream>
#include <queue>
using namespace std;

int housemap[20][20];

int horiMoveR[] = { 0,1 };
int horiMoveC[] = { 1,1 };
int vertMoveR[] = { 1,1 };
int vertMoveC[] = { 0,1 };
int diagMoveR[] = { 0,1,1 };
int diagMoveC[] = { 1,0,1 };

struct pipe {
	int r;
	int c;
	int state;
};

int main() {

	int n; cin >> n;
	//0,1 -> n-1,n-1
	int state = 0;  // 가로 0 세로 1 대각 2
	int r = 0, c = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> housemap[i][j];
		}
	}

	queue<pipe> q;
	q.push({ 0,1,0 });
	int cnt = 0;
	if (housemap[n - 1][n - 1] == 1) {
		cout << 0;
		return 0;
	}
	while (!q.empty()) {
		pipe p = q.front(); q.pop();
		if (p.r == n - 1 && p.c == n - 1) {
			cnt++;
			continue;
		}
		if (p.state == 0) {
			for (int i = 0; i < 2; i++) {
				int nr = p.r + horiMoveR[i];
				int nc = p.c + horiMoveC[i];
				if (i == 0) {
					if (nr >= n || nc >= n) continue;
					if (housemap[nr][nc] == 1) continue;
					q.push({ nr, nc, 0 });
				}
				else {
					if (nr >= n || nc >= n) continue;
					if (housemap[nr][nc] == 1 ||
						housemap[nr-1][nc] == 1 ||
						housemap[nr][nc-1] == 1) continue;
					q.push({ nr, nc, 2 });
				}
			}
		}
		else if (p.state == 1) {
			for (int i = 0; i < 2; i++) {
				int nr = p.r + vertMoveR[i];
				int nc = p.c + vertMoveC[i];
				if (i == 0) {
					if (nr >= n || nc >= n) continue;
					if (housemap[nr][nc] == 1) continue;
					q.push({ nr, nc, 1 });
				}
				else {
					if (nr >= n || nc >= n) continue;
					if (housemap[nr][nc] == 1 ||
						housemap[nr - 1][nc] == 1 ||
						housemap[nr][nc - 1] == 1) continue;
					q.push({ nr, nc, 2 });
				}
			}
		}
		else if (p.state == 2) {
			for (int i = 0; i < 3; i++) {
				int nr = p.r + diagMoveR[i];
				int nc = p.c + diagMoveC[i];
				if (i < 2) {
					if (nr >= n || nc >= n) continue;
					if (housemap[nr][nc] == 1) continue;
					q.push({ nr, nc, i });
				}
				else {
					if (nr >= n || nc >= n) continue;
					if (housemap[nr][nc] == 1 ||
						housemap[nr - 1][nc] == 1 ||
						housemap[nr][nc - 1] == 1) continue;
					q.push({ nr, nc, 2 });
				}
			}
		}
	}

	cout << cnt;
	return 0;
}