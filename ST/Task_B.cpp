#include <bits/stdc++.h>

using namespace std;


vector<int> tree;
vector<int> a;

void init(int i, int l, int r) {
    if (l + 1 == r) { 
        tree[i] = a[l];
    } else {
        int mid = (l + r) / 2;
        init(2 * i + 1, l, mid); init(2 * i + 2, mid, r);
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
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
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    }
}


int get_max(int i, int l, int r, int q_l, int q_r) {
    if (q_r <= l || q_l >= r) {
        return -INT_MAX;
    }

    if (q_l <= l && q_r >= r) {
        return tree[i];
    }

    return max(get_max(2 * i + 1, l, (l + r) / 2, q_l, q_r), get_max(2 * i + 2, (l + r) / 2, r, q_l, q_r));
}


int main() {
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
        int cmd, a, b;
        cin >> cmd >> a >> b;
        if (cmd == 1) {
            cout << get_max(0, 0, n, a, b + 1) << '\n';
        } else {
            change(0, 0, n, a, b);
        }
    }
}
