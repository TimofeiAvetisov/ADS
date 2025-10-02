#include <bits/stdc++.h>

using namespace std;


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        string ans;
        vector<string> answer;
        answer.reserve(s.size());

        for (auto c : s) {
            if (c == 'D') {
                ans.push_back('0');
            } else {
                if (!ans.empty()) {
                    answer.push_back(ans);
                }
                while (!ans.empty() && ans.back() == '1') {
                    ans.pop_back();
                }
                if (!ans.empty()) {
                    ans.back() = '1';
                }
            }
        }
        if (!ans.empty()) {
            answer.push_back(ans);
        }
        cout << answer.size() << '\n';
        for (auto &a : answer) {
            cout << a << '\n';
        }
    }
}
