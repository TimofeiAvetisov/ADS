#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tmp;
    int ans = 0;
    while(cin >> tmp) {
        ans += tmp;
        cout << ans << ' ';
    }
} 