#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> tree;
vector<int> lazy;
vector<int> a;

void push(int i, int l, int r) {
    if (lazy[i] != 0) {
        tree[i] += lazy[i] * (r - l);
        if (l + 1 != r) {
            lazy[2 * i  + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        lazy[i] = 0;
    }
}

void init(int i, int l, int r) {
    if (l + 1 == r) { 
        tree[i] = a[l];
    } else {
        int mid = (l + r) >> 1;
        init(2 * i + 1, l, mid); 
        init(2 * i + 2, mid, r);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

void range_add(int i, int l, int r, int q_l, int q_r, int delta) {
    push(i, l, r);
    if (q_r <= l || q_l >= r) {
        return;
    }

    if (q_l <= l && q_r >= r) {
        lazy[i] += delta;
        push(i, l, r);
    } else {
        int mid = (l + r) >> 1;
        range_add(2*i+1, l, mid, q_l, q_r, delta);
        range_add(2*i+2, mid, r, q_l, q_r, delta);
        tree[i] = tree[2*i+1] + tree[2*i+2];
    }
}

int get_sum(int i, int l, int r, int q_l, int q_r) {
    push(i, l, r);
    if (q_r <= l || q_l >= r) {
        return 0;
    }

    if (q_l <= l && q_r >= r) {
        return tree[i];
    }

    int mid = (l + r) >> 1;
    return get_sum(2*i+1, l, mid, q_l, q_r) + get_sum(2*i+2, mid, r, q_l, q_r);
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    a.resize(n);
    tree.resize(4 * n);
    lazy.resize(4 * n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    init(0, 0, n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int cmd, l, r, val;
        cin >> cmd;
        if (cmd == 1) {
            cin >> l >> r;
            cout << get_sum(0, 0, n, l, r + 1) << '\n';
        } else {
            cin >> l >> r >> val;
            range_add(0, 0, n, l, r + 1, val);
        }
    }
}