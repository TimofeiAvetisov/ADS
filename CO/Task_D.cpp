#include <bits/stdc++.h>

using namespace std;

void perm(int last_used, string current, int len, int n, int k) {
    if (len == k) {
        cout << current << '\n';
        return;
    }

    for (int i = last_used + 1; i < n - k + len + 2; ++i) {
        if (len == 0) {
            perm(i, to_string(i), len + 1, n, k);
            continue;
        }
        perm(i, current + ' ' + to_string(i), len + 1, n, k);

    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    perm(0, "", 0, n, k);
}