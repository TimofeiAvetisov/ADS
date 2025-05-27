#include <bits/stdc++.h>

using namespace std;

vector<multiset<int>> tree;
vector<int> a;

void init(int i, int l, int r) {
    if (l == r - 1) {
        tree[i] = {a[l]};
    } else {
        int mid = (l + r) / 2;
        init(2 * i + 1, l, mid);
        init(2 * i + 2, mid, r);
        tree[i].insert(tree[2 * i + 1].begin(), tree[2 * i + 1].end());
        tree[i].insert(tree[2 * i + 2].begin(), tree[2 * i + 2].end());
    }
}

int get_ans(int i, int l, int r, int q_l, int q_r, int val) {
    if (r <= q_l || l >= q_r) {
        return INT_MAX;
    }

    if (q_l <= l && r <= q_r) {
        auto it = tree[i].upper_bound(val);
        if (it != tree[i].end()) {
            return *it;
        }
        return INT_MAX;
    }

    int mid = (l + r) / 2;
    return min(get_ans(2 * i + 1, l, mid, q_l, q_r, val),
               get_ans(2 * i + 2, mid, r, q_l, q_r, val));
}

void change(int i, int l, int r, int pos, int val) {
    if (pos < l || pos >= r) {
        return;
    }

    if (l == r - 1) {
        tree[i].erase(tree[i].find(a[pos]));
        tree[i].insert(val);
        a[pos] = val;
        return;
    }

    tree[i].erase(tree[i].find(a[pos]));
    tree[i].insert(val);

    int mid = (l + r) / 2;
    change(2 * i + 1, l, mid, pos, val);
    change(2 * i + 2, mid, r, pos, val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            int ans = get_ans(0, 0, n, l, r + 1, k);
            if (ans == INT_MAX) {
                cout << "NONE\n";
            } else {
                cout << ans << '\n';
            }
        } else {
            int pos, b;
            cin >> pos >> b;
            change(0, 0, n, pos, b);
        }
    }
}