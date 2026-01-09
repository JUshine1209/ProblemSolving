#include <iostream>
#include <vector>
#include <queue>
#include <deque>
//#include <iomanip>
using namespace std;

int map[100][100] = { 0, };
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

queue<pair<int, char>> turn_time_q;
deque<pair<int, int>> snake_coord_dq;

int N;
int K;
int L;
int dir = 1;

/*
void print_map(int R, int C) {
	cout << "########## PRINT MAP #########" << endl;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cout << setw(1) << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "##############################" << endl;
}
*/

int main() {

	cin >> N;
	
	cin >> K;
	int r, c;
	for (int i = 0; i < K; i++) {
		cin >> r >> c;
		r--; c--;
		map[r][c] = 1;
	}

	cin >> L;
	int t; char d;
	for (int i = 0; i < L; i++) {
		cin >> t >> d;
		turn_time_q.push(make_pair(t, d));
	}

	int time = 0;
	int head_r = 0;
	int head_c = 0;
	int next_r = 0;
	int next_c = 0;
	int turn_time = 0;
	char turn_dir = 0;
	snake_coord_dq.push_front(make_pair(0, 0));
	map[0][0] = 2;
	while (1) {
		time++;

		head_r = snake_coord_dq.front().first;
		head_c = snake_coord_dq.front().second;

		next_r = head_r + dr[dir];
		next_c = head_c + dc[dir];

		if (next_r < 0 || next_r >= N) break;
		if (next_c < 0 || next_c >= N) break;
		if (map[next_r][next_c] == 2) break;

		snake_coord_dq.push_front(make_pair(next_r, next_c));
		if (map[next_r][next_c] == 0) {
			map[snake_coord_dq.back().first][snake_coord_dq.back().second] = 0;
			snake_coord_dq.pop_back();
		}

		map[next_r][next_c] = 2;

		if (!turn_time_q.empty()) {
			turn_time = turn_time_q.front().first;
			turn_dir = turn_time_q.front().second;

			if (time == turn_time) {
				turn_time_q.pop();
				if (turn_dir == 'L') {
					dir--;
					if (dir < 0) dir = 3;
				}
				if (turn_dir == 'D') {
					dir++;
					if (dir > 3) dir = 0;
				}
			}
		}

		//print_map(N, N);
	}

	cout << time;

	return 0;
}