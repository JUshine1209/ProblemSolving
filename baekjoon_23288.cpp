#include <iostream>
#include <queue>
using namespace std;

//top, up, right, left, down, bottom;
int dice[] = {1,2,3,4,5,6};

//direction array: ↑→↓←
int rdir[] = { -1,0,1,0 };
int cdir[] = { 0,1,0,-1 };

struct node {
	int r;
	int c;
};

int dMap[20][20]{};
int visited[20][20]{};

void diceNumChange(int, int);
void diceDirMove(int);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(); cout.tie();
	
	int n, m, k; cin >> n >> m >> k;
	int score = 0; int d = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> dMap[i][j];
		}
	}
	queue<node> q;
	
	int diceR = 0; int diceC = 0;
	for (int i = 0; i < k; i++) {
		diceR += rdir[d]; diceC += cdir[d];
		if (diceR < 0) {
			diceR = 1; d = 2;
		}
		else if (diceR >= n) {
			diceR = n - 2; d = 0;
		}
		else if (diceC < 0) {
			diceC = 1; d = 1;
		}
		else if (diceC >= m) {
			diceC = m-2; d = 3;
		}
		diceDirMove(d);
		for (int a = 0; a < n; a++) {
			for (int b = 0; b < m; b++) {
				visited[a][b] = 0;
			}
		}
		q.push({ diceR, diceC });
		int cnt = 1;

		visited[diceR][diceC] = 1;
		while (!q.empty()) {
			node now = q.front(); q.pop();
			for (int j = 0; j < 4; j++) {
				int nr = now.r + rdir[j];
				int nc = now.c + cdir[j];
				if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
				if (visited[nr][nc]) continue;
				if (dMap[nr][nc] != dMap[diceR][diceC]) continue;
				visited[nr][nc] = 1;
				cnt++;
				q.push({ nr,nc });
			}
		}
		score += cnt * dMap[diceR][diceC];
		if (dice[5] > dMap[diceR][diceC]) {
			d++;
			if (d == 4) d = 0;
		}
		else if (dice[5] < dMap[diceR][diceC]) {
			d--;
			if (d == -1) d = 3;
		}
	}

	cout << score;

	return 0;
}

void diceNumChange(int a, int b) {
	int tmp = dice[0];
	dice[0] = dice[a];
	dice[a] = dice[5];
	dice[5] = dice[b];
	dice[b] = tmp;
}

void diceDirMove(int dir) {
	switch (dir)
	{
	case 0:
		diceNumChange(4, 1);
		break;
	case 1:
		diceNumChange(3, 2);
		break;
	case 2:
		diceNumChange(1, 4);
		break;
	case 3:
		diceNumChange(2, 3);
		break;
	default:
		break;
	}
}
