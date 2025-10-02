#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> f(n);
    f[0] = 1;
    for (int i = 1; i < n; ++i) {
        f[i] = f[i - 1] * i;
    }


    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }

    --k;

    for (int i = 0; i < n; ++i) {
        cout << nums[k / f[n - i - 1]] << ' ';
        nums.erase(nums.begin() + k / f[n - i - 1]);
        k %= f[n - i - 1];
    }
}

