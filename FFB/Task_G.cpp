#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n, INT_MAX);
    d[0] = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int w = ((i + 1) * 179 + (j + 1) * 719) % 1000 - 500;
            d[j] = min(d[j], d[i] + w);
        }
    }

    cout << d[n - 1];
}