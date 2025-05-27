#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> tree;
vector<int> a;

void init(int i, int l, int r) {
    if (l + 1 == r) { 
        tree[i] = a[l];
    } else {
        int mid = (l + r) / 2;
        init(2 * i + 1, l, mid); init(2 * i + 2, mid, r);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

void change(int i, int l, int r, int q_i, int delta) {
    if (q_i < l || q_i >= r) {
        return;
    }

    if (r == l + 1) {
        tree[i] = delta;
    } else {
        change(2 * i + 1, l, (l + r) / 2, q_i, delta);
        change(2 * i + 2, (l + r) / 2, r, q_i, delta);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

int find_prefix(int i, int l, int r, int k) {
    if (tree[i] < k) {
        return -1;
    }

    if (l + 1 == r) {
        return l;
    }

    int mid = (l + r) >> 1;
    if (tree[2 * i + 1] >= k) {
        return find_prefix(2 * i + 1, l, mid, k);
    } else {
        return find_prefix(2 * i + 2, mid, r, k - tree[2 * i + 1]);
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    a.resize(n);
    tree.resize(4 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    init(0, 0, n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int k;
            cin >> k;
            if (k == 0) {
                cout << k << '\n';
                continue;
            }
            int ans = find_prefix(0, 0, n, k);
            if (ans == -1) {
                cout << "NONE\n";
            } else {
                cout << ans + 1 << '\n';
            }
        } else {
            int pos, b;
            cin >> pos >> b;
            change(0, 0, n, pos, b);
        }
    }
}