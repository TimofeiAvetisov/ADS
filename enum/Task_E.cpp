#include <bits/stdc++.h>

using namespace std;

vector<int> table;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> m >> n;
    if (m > n || (n * (n + 1) / 2) % m != 0) {
        cout << "NO";
        return 0;
    }


    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }

    int target = (n * (n + 1) / 2) / m;
    if (target < n) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    while(!nums.empty()) {
        int cur = 0;
        int cnt = 0;
        string res = "";
        for (int i = nums.size() - 1; i >= 0 && cur != target; --i) {
            if (cur + nums[i] <= target) {
                cur += nums[i];
                res += ' ' + to_string(nums[i]);
                ++cnt;
                nums.erase(nums.begin() + i);
            }
        }
        
        cout << cnt << res << '\n';
    }
}