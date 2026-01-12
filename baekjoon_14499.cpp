#include <iostream>
using namespace std;

int N;
int M;
int x;
int y;
int K;

int map[20][20] = { 0, };

//   2
// 4 1 3
//   5
//   6

//              0 위 북 동 서 남 아래
int dice[7] = { 0, };

int dr[5] = {0,0,0,-1,1};
int dc[5] = {0,1,-1,0,0};
int temp = 0;

void move_right() {
	temp = dice[1];
	dice[1] = dice[4];
	dice[4] = dice[6];
	dice[6] = dice[3];
	dice[3] = temp;
}

void move_left() {
	temp = dice[1];
	dice[1] = dice[3];
	dice[3] = dice[6];
	dice[6] = dice[4];
	dice[4] = temp;
}

void move_up() {
	temp = dice[1];
	dice[1] = dice[5];
	dice[5] = dice[6];
	dice[6] = dice[2];
	dice[2] = temp;
}

void move_down() {
	temp = dice[1];
	dice[1] = dice[2];
	dice[2] = dice[6];
	dice[6] = dice[5];
	dice[5] = temp;
}

void move_dice(int cmd) {
	if (cmd == 1) move_right();
	else if (cmd == 2) move_left();
	else if (cmd == 3) move_up();
	else if (cmd == 4) move_down();
	else return;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> x >> y >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	int cmd = 0;
	int next_r = 0;
	int next_c = 0;
	for (int i = 0; i < K; i++) {
		cin >> cmd;
		next_r = x + dr[cmd];
		next_c = y + dc[cmd];
		if (next_r < 0 || next_r >= N) continue;
		if (next_c < 0 || next_c >= M) continue;
		x = next_r;
		y = next_c;
		move_dice(cmd);
		if (map[x][y]) {
			dice[6] = map[x][y];
			map[x][y] = 0;
		}
		else map[x][y] = dice[6];

		cout << dice[1] << '\n';
	}

	return 0;
}