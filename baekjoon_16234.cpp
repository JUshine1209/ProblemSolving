#include <iostream>
#include <queue>;
using namespace std;

int A[50][50];
int unite[50][50];
int uniteSum[1400];
int uniteNations[1400];

int rdir[] = { -1,1,0,0 };
int cdir[] = { 0,0,-1,1 };

struct nation {
	int r;
	int c;
	int queuefirst;
};

int main() {
	int N, L, R; cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}
	int moveCnt = 0;
	bool moveFlag = true;
	queue<nation> q;

	while (moveFlag) {
		moveFlag = false;
		int uniteNum = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				unite[i][j] = 0;
			}
		}
		for (int i = 0; i < 1400; i++) {
			uniteSum[i] = 0;
			uniteNations[i] = 0;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (unite[i][j]) continue;
				q.push({ i, j, 1 });
				while (!q.empty()) {
					nation now = q.front(); q.pop();
					for (int i = 0; i < 4; i++) {
						int nr = now.r + rdir[i];
						int nc = now.c + cdir[i];
						if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
						if (unite[nr][nc] == uniteNum) continue;
						int diff = abs(A[now.r][now.c] - A[nr][nc]);
						if (diff < L || R < diff) continue;
						if (now.queuefirst) {
							now.queuefirst = 0;
							uniteNum += 1;
						}
						unite[nr][nc] = uniteNum;
						uniteSum[uniteNum] += A[nr][nc];
						uniteNations[uniteNum] += 1;
						q.push({ nr,nc,0 });
					}
				}
			}
		}

		if (uniteNum > 1) {
			moveFlag = true;
			moveCnt++;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (unite[i][j]) {
						A[i][j] = uniteSum[unite[i][j]] / uniteNations[unite[i][j]];
					}
				}
			}
		}
	}

	cout << moveCnt;
	return 0;
}