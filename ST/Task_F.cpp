#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> tree;
vector<int> a;
vector<int> ca;

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


int get_ans(int i, int l, int r, int k) {
    if (tree[i] < k || k <= 0) {
        return 0;
    }

    if (r == l + 1) {
        return ca[l];
    }

    return get_ans(2 * i + 1, l, (l + r) / 2, k) + get_ans(2 * i + 2, (l + r) / 2, r, k - tree[2 * i + 1]);
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    a.resize(n); ca.resize(n);
    tree.resize(4 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ca[i] = a[i];
        a[i] = (abs(a[i]) + 1) % 2;
    }

    init(0, 0, n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int k, l, r;
            cin >> l >> r >> k;
            if (get_sum(0, 0, n, l, r + 1) < k) {
                cout << "NONE\n";
            } else {
                k += get_sum(0, 0, n, 0, l);
                cout << get_ans(0, 0, n, k) << '\n';
            }
        } else {
            int pos, b;
            cin >> pos >> b;
            ca[pos] = b;
            change(0, 0, n, pos, (abs(b) + 1) % 2);
        }
    }
}