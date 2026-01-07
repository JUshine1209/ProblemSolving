#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

int N = 0;
int answer = 0;
int board[20][20] = { 0, };

void print_board(int R, int C) {
	cout << "########## PRINT MAP #########" << endl;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cout << setw(4) << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << "##############################" << endl;
}

// 1. 시계 90도 (Clockwise 90)
void rotate_90() {
	int temp[20][20];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			temp[j][N - 1 - i] = board[i][j];
		}
	}
	memcpy(board, temp, sizeof(board));
}

// 2. 시계 180도 (Clockwise 180)
void rotate_180() {
	int temp[20][20];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			temp[N - 1 - i][N - 1 - j] = board[i][j];
		}
	}
	memcpy(board, temp, sizeof(board));
}

// 3. 시계 270도 (Clockwise 270)
void rotate_270() {
	int temp[20][20];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			temp[N - 1 - j][i] = board[i][j];
		}
	}
	memcpy(board, temp, sizeof(board));
}

void move_merge(int dir) {

	if (dir == 1) rotate_90();
	if (dir == 2) rotate_180();
	if (dir == 3) rotate_270();

	for (int i = 0; i < N; ++i) {
		int temp[20] = { 0, };
		int idx = 0;

		for (int j = 0; j < N; ++j) {
			if (board[i][j] == 0) continue;

			if (temp[idx] == 0) {
				temp[idx] = board[i][j];
			}
			else if (temp[idx] == board[i][j]) {
				temp[idx] *= 2;
				if (answer < temp[idx]) answer = temp[idx];
				idx++;
			}
			else {
				idx++;
				temp[idx] = board[i][j];
			}
		}
		for (int j = 0; j < N; ++j) {
			board[i][j] = temp[j];
		}
	}

	if (dir == 1) rotate_270();
	if (dir == 2) rotate_180();
	if (dir == 3) rotate_90();
}

void dfs(int depth) {
	// print_board(N, N);
	if (depth == 5) return;

	int backup_board[20][20] = { 0, };
	memcpy(backup_board, board, sizeof(board));

	for (int dir = 0; dir < 4; ++dir) {
		move_merge(dir);
		dfs(depth + 1);
		memcpy(board, backup_board, sizeof(board));
	}
}

int main() {
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (answer < board[i][j]) answer = board[i][j];
		}
	}

	dfs(0);

	cout << answer;

	return 0;
}