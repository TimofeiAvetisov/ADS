#include <bits/stdc++.h>

using namespace std;

int a(int n, int k, vector<int>& f) {
    return f[n] / f[n - k];
}

int main() {
    //std::ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    //cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }

    vector<int> f(n);
    f[0] = 1;
    for (int i = 1; i < n; ++i) {
        f[i] = f[i - 1] * i;
    }

    long long ans = 0;

    vector<int> perm(k);

    for (int i = 0; i < k; ++i) {
        cin >> perm[i];
    }

    for (int i = 0; i < k; ++i) {
        int mlt = 0;
        while(nums[mlt] < perm[i]) {
            ++mlt;
        }
        
        
        ans += mlt * a(n - i - 1, k - i - 1, f);
        nums.erase(nums.begin() + mlt);
    }

    cout << ans + 1;
}