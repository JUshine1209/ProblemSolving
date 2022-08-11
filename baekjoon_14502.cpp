#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int rdir[] = {-1,1,0,0};
int cdir[] = {0,0,-1,1};

int labMap[8][8]{};
int simMap[8][8]{};

struct Node {
	int r;
	int c;
};

vector<Node> start;
vector<Node> blankSpace;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(); cout.tie();
	
	int n, m; cin >> n >> m;
	int initCnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> labMap[i][j];
			if (labMap[i][j] == 0) {
				blankSpace.push_back({ i,j });
				initCnt++;
			}
			else if (labMap[i][j] == 2) start.push_back({ i,j });
		}
	}

	queue<Node> q;
	int maxcnt = 0;

	for (int i = 0; i < blankSpace.size(); i++) {
		for (int j = i + 1; j < blankSpace.size(); j++){
			for (int k = j + 1; k < blankSpace.size(); k++) {
				
                int cnt = initCnt - 3;
				for (int a = 0; a < n; a++) {
					for (int b = 0; b < m; b++) {
						simMap[a][b] = labMap[a][b];
					}
				}
				simMap[blankSpace[i].r][blankSpace[i].c] = 1;
				simMap[blankSpace[j].r][blankSpace[j].c] = 1;
				simMap[blankSpace[k].r][blankSpace[k].c] = 1;

				for (int a = 0; a < start.size(); a++) {
					q.push(start[a]);
					while (!q.empty()) {

						Node now = q.front(); q.pop();
						for (int b = 0; b < 4; b++) {
							int nr = now.r + rdir[b];
							int nc = now.c + cdir[b];

							if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
							if (simMap[nr][nc] == 1 || simMap[nr][nc] == 2) continue;

							simMap[nr][nc] = 2;
							cnt--;
							q.push({ nr, nc });
                            
						}
					}
				}
				if (cnt > maxcnt) maxcnt = cnt;
			}
		}
	}

	cout << maxcnt;

	return 0;
}