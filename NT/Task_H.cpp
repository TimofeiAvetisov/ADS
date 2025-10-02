#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, k;
    cin >> N >> k;

    vector<pair<int, int>> f;
    for (int i = 2; i * i <= k; ++i) {
        if (k % i == 0) {
            int pw = 0;
            while(!(k % i)) {
                k /= i;
                ++pw;
            }
            f.emplace_back(i, pw);
        }
    }

    if (k > 1) {
        f.emplace_back(k, 1);
    }

    int answer = INT_MAX;
    for (auto &[p, x] : f) {
        int cnt = 0;
        int n = N;
        while (n > 0) {
            n /= p;
            cnt += n;
        }

        answer = min(answer, cnt / x);
    }

    cout << answer;
}