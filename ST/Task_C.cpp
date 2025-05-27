#include <bits/stdc++.h>

using namespace std;


vector<int> tree;
vector<int> a;

int ind_max(int ind_a, int ind_b) {
    if (ind_a < 0 && ind_b < 0) {
        return ind_a;
    }
    if((ind_a < 0 && ind_b >= 0) || (ind_a >= 0 && ind_b < 0)) {
        return max(ind_a, ind_b);
    }

    if (a[ind_a] > a[ind_b]) {
        return ind_a;
    }

    return ind_b;
}

void init(int i, int l, int r) {
    if (l + 1 == r) { 
        tree[i] = l;
    } else {
        int mid = (l + r) / 2;
        init(2 * i + 1, l, mid); init(2 * i + 2, mid, r);
        tree[i] = ind_max(tree[2 * i + 1], tree[2 * i + 2]);
    }
}


void change(int i, int l, int r, int q_i, int delta) {
    if (q_i < l || q_i >= r) {
        return;
    }

    if (r == l + 1) {
        a[l] = delta;
    } else {
        change(2 * i + 1, l, (l + r) / 2, q_i, delta);
        change(2 * i + 2, (l + r) / 2, r, q_i, delta);
        tree[i] = ind_max(tree[2 * i + 1], tree[2 * i + 2]);
    }
}


int get_ind_max(int i, int l, int r, int q_l, int q_r) {
    if (q_r <= l || q_l >= r) {
        return -1;
    }

    if (q_l <= l && q_r >= r) {
        return tree[i];
    }

    return ind_max(get_ind_max(2 * i + 1, l, (l + r) / 2, q_l, q_r), get_ind_max(2 * i + 2, (l + r) / 2, r, q_l, q_r));
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
            cout << get_ind_max(0, 0, n, a, b + 1) << '\n';
        } else {
            change(0, 0, n, a, b);
        }
    }
}
