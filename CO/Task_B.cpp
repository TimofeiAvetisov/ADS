#include <bits/stdc++.h>
#include <bitset>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    string s(n, '0');
    for (int i = 0; i < k; ++i) {
        s[n - i - 1] = '1';
    }

    cout << s << '\n';
    while(next_permutation(s.begin(), s.end())) {
        cout << s << '\n';
    }
}