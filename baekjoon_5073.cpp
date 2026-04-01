#include <iostream>
using namespace std;

int main() {
	int a, b, c;
	while (1) {
		cin >> a >> b >> c;
		if (a == 0 && b == 0 && c == 0) break;
		if (a + b <= c || a + c <= b || b + c <= a) {
			cout << "Invalid" << endl;
			continue;
		}
		if (a == b && b == c) cout << "Equilateral" << endl;
		else if (a == b || a == c || b == c) cout << "Isosceles" << endl;
		else cout << "Scalene" << endl;
	}
	return 0;
}