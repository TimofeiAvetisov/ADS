#include <bits/stdc++.h>

using namespace std;

void solve(int n, int last_used, int cur_sum, string ans) {
    if (cur_sum == n) {
        cout << ans << '\n';
        return;
    }

    for (int i = 1; i < min(n - cur_sum + 1, last_used + 1); ++i) {
        if (ans.empty()) {
            solve(n, i, cur_sum + i, to_string(i));
            continue;
        }
        solve(n, i, cur_sum + i, ans + " " + to_string(i));
    }
}

void print_sums(size_t n) {
    solve(n, n + 1, 0, "");
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;
    print_sums(n);
}