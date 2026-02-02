#include <iostream>
#include <algorithm>

using namespace std;

int T[17] = { 0, };
int P[17] = { 0, };
int DP[17] = { 0, };

int main() {
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> T[i] >> P[i];
	}

	for (int i = N; i >= 1; i--) {
		int next_day = i + T[i];

		if (next_day <= N + 1) {
			DP[i] = max(DP[i + 1], P[i] + DP[next_day]);
		}
		else {
			DP[i] = DP[i + 1];
		}
	}

	cout << DP[1] << '\n';

	return 0;
}