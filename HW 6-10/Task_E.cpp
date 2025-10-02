#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int MAXM = 1000;

int n, m;
int t[MAXN+1][MAXM+1];

int sum(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            res += t[i][j];
    return res;
}

int sum(int x1, int y1, int x2, int y2) {
    return sum(x2,y2)
         - sum(x1-1,y2)
         - sum(x2,y1-1)
         + sum(x1-1,y1-1);
}

void add(int i, int j, int x) {
    for (int ii = i; ii <= n; ii += ii & -ii) {
        for (int jj = j; jj <= m; jj += jj & -jj) {
            t[ii][jj] += x;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int q;
    cin >> n >> m >> q;
    vector<vector<int>> matr(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matr[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            add(i + 1, j + 1, matr[i][j]);
        }
    }

    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << sum(x1,y1,x2,y2) << "\n";
    }
}
