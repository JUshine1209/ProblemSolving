#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int origin[10][10];
int nation[10][10];
int visited[10][10];

int rdir[] = { -1,1,0,0 };
int cdir[] = { 0,0,-1,1 };
int n, m;
int parent[7];

struct crd {
	int r;
	int c;
};

struct edge {
	int a;
	int b;
	int cost;
};

vector<edge> e;

bool cmp(edge a, edge b) {
	if (a.cost < b.cost) return true;
	if (a.cost > b.cost) return false;
	return false;
}

void init_visited();
void make_nation(int, int, int);
void avail_bridge(int, int, int);
int iFind(int);
void iUnion(int, int);

int main() {
	cin >> n >> m;
	for (int i = 0; i < 7; i++) parent[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> origin[i][j];
		}
	}

	int natnum = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (origin[i][j] && !nation[i][j]) {
				init_visited();
				make_nation(i, j, natnum);
				natnum++;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (nation[i][j]) {
				avail_bridge(i, j, nation[i][j]);
			}
		}
	}

	sort(e.begin(), e.end(), cmp);
	int sum = 0;
	int cnt = 0;
	for (int i = 0; i < e.size(); i++) {
		edge now = e[i];
		if (iFind(now.a) == iFind(now.b)) continue;
		sum += now.cost;
		cnt++;
		iUnion(now.a, now.b);
	}
	if (cnt == natnum - 2) cout << sum;
	else cout << -1;

	return 0;
}

void init_visited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = 0;
		}
	}
}

void make_nation(int r, int c, int num) {
	nation[r][c] = num;
	queue<crd> q;
	q.push({ r,c });
	while (!q.empty()) {
		crd now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = now.r + rdir[i];
			int nc = now.c + cdir[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (!origin[nr][nc])continue;
			if (nation[nr][nc]) continue;
			nation[nr][nc] = num;
			q.push({ nr,nc });
		}
	}
}

void avail_bridge(int r, int c, int num) {
	// left
	for (int i = 1; i < m; i++) {
		int nc = c - i;
		if (nc < 0) break;
		if (nation[r][nc] == num) break;
		if (nation[r][nc] == 0) continue;
		if (nation[r][nc] != num) {
			if (i < 3) break;
			else {
				e.push_back({ num, nation[r][nc], i - 1 });
				break;
			}
		}
	}
	// right
	for (int i = 1; i < m; i++) {
		int nc = c + i;
		if (nc >= m) break;
		if (nation[r][nc] == num) break;
		if (nation[r][nc] == 0) continue;
		if (nation[r][nc] != num) {
			if (i < 3) break;
			else {
				e.push_back({ num, nation[r][nc], i - 1 });
				break;
			}
		}
	}
	// up
	for (int i = 1; i < n; i++) {
		int nr = r - i;
		if (nr < 0) break;
		if (nation[nr][c] == num) break;
		if (nation[nr][c] == 0) continue;
		if (nation[nr][c] != num) {
			if (i < 3) break;
			else {
				e.push_back({ num, nation[nr][c], i - 1 });
				break;
			}
		}
	}
	// down
	for (int i = 1; i < n; i++) {
		int nr = r + i;
		if (nr >= n) break;
		if (nation[nr][c] == num) break;
		if (nation[nr][c] == 0) continue;
		if (nation[nr][c] != num) {
			if (i < 3) break;
			else {
				e.push_back({ num, nation[nr][c], i - 1 });
				break;
			}
		}
	}
}

int iFind(int node) {
	if (node == parent[node]) return node;
	return parent[node] = iFind(parent[node]);
}

void iUnion(int a, int b) {
	int pa = iFind(a);
	int pb = iFind(b);
	if (pa == pb) return;
	parent[pb] = pa;
}