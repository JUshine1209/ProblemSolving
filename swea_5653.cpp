#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int cmap[450][450];

struct crd {
	int r;
	int c;
	int inactive;
	int active;
};

bool operator < (crd a, crd b) {
	if (cmap[a.r][a.c] > cmap[b.r][b.c]) return false;
	if (cmap[a.r][a.c] < cmap[b.r][b.c]) return true;
	return false;
}

int rdir[] = { -1,1,0,0 };
int cdir[] = { 0,0,-1,1 };

priority_queue<crd> bfs(priority_queue<crd>);

int main(int argc, char** argv) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i < 450; i++) 
			for (int j = 0; j < 450; j++)
				cmap[i][j] = 0;

		int n, m, k; cin >> n >> m >> k;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> cmap[i + 200][j + 200];

		int ans = 0;
		priority_queue<crd> q;
		for (int i = 200; i < 200 + n; i++)
			for (int j = 200; j < 200 + m; j++)
				if (cmap[i][j]) q.push({ i,j,cmap[i][j],0 });

		for (int i = 0; i < k; i++)
			q = bfs(q);

		ans = q.size();
		cout << '#' << tc << ' ' << ans << '\n';
	}
	
}

priority_queue<crd> bfs(priority_queue<crd> q) {
	priority_queue<crd> next;

	while (!q.empty()) {
		crd now = q.top(); q.pop();

		now.inactive--;
		if (now.inactive < 0) {
			if (now.active == 0) {
				for (int i = 0; i < 4; i++) {
					int nr = now.r + rdir[i];
					int nc = now.c + cdir[i];
					if (cmap[nr][nc] != 0) continue;
					cmap[nr][nc] = cmap[now.r][now.c];
					next.push({ nr,nc, cmap[nr][nc],0 });
				}
			}
			now.active++;
		}
		if (now.active < cmap[now.r][now.c]) next.push(now);
	}
	return next;
}