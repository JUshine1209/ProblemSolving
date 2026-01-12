#include <iostream>
#include <vector>
using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, B, C;
	long long ans = 0;
	vector<int> test_loc;
	cin >> N;
	test_loc.resize(N);

	for (int i = 0; i < N; i++) {
		cin >> test_loc[i];
	}

	cin >> B >> C;
	for (int i = 0; i < N; i++) {
		ans++;
		if (test_loc[i] <= B) continue;

		ans += (test_loc[i] - B + C - 1) / C;
	}
	
	cout << ans;
	return 0;
}