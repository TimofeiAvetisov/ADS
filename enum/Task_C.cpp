#include <bits/stdc++.h>

using namespace std;

int n;

void generate(string s, int ttl, int pos, vector<int> q) {
    if (s.size() == n) {
        cout << s << '\n';
        return;
    }

    if (ttl < n / 2) {
        q[pos + 1] = 1;
        generate(s + '(', ttl + 1, pos + 1, q);
    }

    if (ttl < n / 2) {
        q[pos + 1] = 2;
        generate(s + '[', ttl + 1, pos + 1, q);
    }

    if (pos != -1 && q[pos] == 1) {
        generate(s + ')', ttl, pos - 1, q);
    }

    if (pos != -1 && q[pos] == 2) {
        generate(s + ']', ttl, pos - 1, q);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    if (n % 2) {
        return 0;
    }
    vector<int> q(n);
    generate("", 0, -1, q);
}