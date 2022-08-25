#include <iostream>
#include <cstdlib>
using namespace std;
void recur(int, int);
int col[15]{};
int cnt = 0;
int main() {
    int n; cin >> n;
    recur(0, n);
    cout << cnt;
    return 0;
}
void recur(int level, int N){
    if(level == N){
        cnt++;
        return;
    }

    for(int i = 0; i < N; i++){
      
        int flag = 1;
        for(int j = 0; j < level; j++){
            if(abs(j-level) == abs(col[j] - i)) flag = 0;
            if(col[j] == i) flag = 0;
        }

        if(flag){
            col[level] = i;
            recur(level+1, N);
            col[level] = 0;
        }
    }
}
