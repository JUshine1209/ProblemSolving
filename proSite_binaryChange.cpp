#include <iostream>
using namespace std;

long long fn(long long n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	long long tmp = n;
	int powNum = 0;
	bool jegopsuFlag = true;
	while (tmp > 0) {
		if (tmp != 1 && tmp % 2 == 1) jegopsuFlag = false;
		tmp /= 2;
		powNum++;
	}
	long long topJegopSu = 1;
	for (int i = 0; i < powNum; i++) topJegopSu *= 2;

	if (jegopsuFlag) {
		return topJegopSu - 1;
	}
	else {
		return topJegopSu - 1 - fn(n - topJegopSu / 2);
	}
}

int main() {
	long long n; cin >> n;
	cout << fn(n);
	return 0;
}