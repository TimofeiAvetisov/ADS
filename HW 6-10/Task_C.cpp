#include <bits/stdc++.h>

using namespace std;

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

int get_sum(int i, int l, int r, int q_l, int q_r) {
    if (q_r <= l || q_l >= r) {
        return 0;
    }

    if (q_l <= l && q_r >= r) {
        return tree[i];
    }

    return get_sum(2 * i + 1, l, (l + r) / 2, q_l, q_r) +  get_sum(2 * i + 2, (l + r) / 2, r, q_l, q_r);
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

    int n = 1e5 + 1;
    a.resize(n, 0);
    tree.resize(4 * n);
    
    init(0, 0, n);

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int cmd, val;
        cin >> cmd >> val;
        if (cmd == 1) {
            val = 1e5 - val;
            change(0, 0, n, val, 1);
            cout << get_sum(0, 0, n, 0, val) << '\n';
        } else {
            int pos = find_prefix(0, 0, n, val + 1);
            change(0, 0, n, pos, 0);
        }
    }
}