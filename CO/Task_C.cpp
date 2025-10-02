#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    string s = "";
    for (int i = 0; i < n; ++i) {
        s += ((i + 1) + '0');
    }

    cout << s << '\n';
    while(next_permutation(s.begin(), s.end())) {
        cout << s << '\n';
    }
}