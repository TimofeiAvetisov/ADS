#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int MAXVERT = 4e6;

int value[MAXVERT], left_ch[MAXVERT], right_ch[MAXVERT];
int root[MAXN + 5];
int nodes = 0;

int build(int l, int r) {
    int v = ++nodes;
    value[v] = 0;
    if (l + 1 < r) {
        int m = (l + r) >> 1;
        left_ch[v] = build(l, m);
        right_ch[v] = build(m, r);
    }
    return v;
}

int update(int v, int l, int r, int pos, int val) {
    int u = ++nodes;
    left_ch[u] = left_ch[v];
    right_ch[u] = right_ch[v];
    value[u] = value[v];
    if (l + 1 == r) {
        value[u] = val;
        return u;
    }
    int m = (l + r) / 2;
    if (pos < m)
        left_ch[u] = update(left_ch[v], l, m, pos, val);
    else
        right_ch[u] = update(right_ch[v], m, r, pos, val);
    value[u] = value[left_ch[u]] + value[right_ch[u]];
    return u;
}

int query(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return value[v];
    int m = (l + r) / 2;
    return query(left_ch[v], l, m, ql, qr) + query(right_ch[v], m, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    root[0] = build(0, n);

    for (int i = 1; i <= q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int ver, pos, val;
            cin >> ver >> pos >> val;
            root[i] = update(root[ver], 0, n, pos, val);
        } else {
            int ver, l, r;
            cin >> ver >> l >> r;
            cout << query(root[ver], 0, n, l, r) << '\n';
            root[i] = root[ver];
        }
    }
}
