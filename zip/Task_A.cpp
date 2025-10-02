#include <bits/stdc++.h>

using namespace std;

inline bool is_power(int n) {
    return n && ((n & (n - 1)) == 0);
}

int find_k(int n) {
    int k = 0;
    while ((1 << k) < n + k + 1) ++ k;
    return k;
}

void code(const string& x) {
    int n = x.size();
    int k = find_k(n);
    int len = n + k;

    vector<int> y(len + 1, 0);

    for (int i = 1, j = 0; i <= len; ++i) {
        if (is_power(i)) continue;
        y[i] = (x[j++] == '1');
    }

    for (int j = 0; j < k; ++j) {
        int pos = 1 << j;
        int tmp = 0;
        for (int i = 1; i <= len; ++i) {
            if (i & pos) tmp ^= y[i];
        }
        y[pos] = tmp;
    }

    string answer;
    answer.reserve(len);
    for (int i = 1; i <= len; ++i) {
        answer.push_back(char('0' + y[i]));
    }
    cout << answer << '\n';

}   

void decode(const string& y) {
    int len = y.size();

    int k = 0;
    while ((1<<k) <= len) ++k;

    vector<int> x(len + 1, 0);
    for (int i = 1; i <= len; ++i) {
        x[i] = (y[i - 1] == '1');
    }

    int res_pos = 0;
    for (int j = 0; j < k; ++j) {
        int pos = 1 << j;
        int tmp = 0;
        for (int i = 1; i <= len; ++i) {
            if (i & pos) tmp ^= x[i];
        }
        if (tmp) res_pos |= pos;
    }

    if (res_pos >= 1 && res_pos <= len) x[res_pos] ^= 1;

    string answer;
    answer.reserve(len);
    for (int i = 1; i <= len; ++i) {
        if (!is_power(i)) answer.push_back(char('0' + x[i]));
    }

    cout << answer << ' ';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int cmd;
    cin >> cmd;

    string s;
    cin >> s;
    if (cmd == 1) {
        code(s);
    } else {
        decode(s);
    }
}