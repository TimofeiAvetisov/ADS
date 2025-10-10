#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5;
const int MAXVERT = 4e6;

int value[MAXVERT], left_ch[MAXVERT], right_ch[MAXVERT];
int root[MAXN];
int to_pop[MAXN], to_push[MAXN];
int qu[MAXN];
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
    if (pos < m) {
        left_ch[u] = update(left_ch[u], l, m, pos, val);
    } else {
        right_ch[u] = update(right_ch[u], m, r, pos, val);
    }
    return u;
}

int query(int v, int l, int r, int pos) {
    if (l + 1 == r) {
        return value[v];
    }
    int m = (l + r) / 2;
    if (pos < m) {
        return query(left_ch[v], l, m, pos);
    }
    
    return query(right_ch[v], m, r, pos);

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    root[0] = build(1, n + 1);
    to_pop[0] = to_push[0] = 0;
    int cur_nodes = 0;

    for (int i = 1; i <= n; ++i) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int t, m;
            cin >> t >> m;

            to_pop[i] = to_pop[t];
            to_push[i] = to_push[t];
            root[i] = root[t];

            qu[++cur_nodes] = m;

            if (to_pop[t] == 0) {
                to_pop[i] = to_push[i] = cur_nodes;
            } else {
                root[i] = update(root[t], 1, n + 1, to_push[t], cur_nodes);
                to_push[i] = cur_nodes;
            }
        } else {
            int t;
            cin >> t;
            cout << qu[to_pop[t]] << '\n';
            int ans = query(root[t], 1, n + 1, to_pop[t]);
            to_pop[i] = ans;
            to_push[i] = (ans == 0 ? 0 : to_push[t]);
            root[i] = root[t];
        }
    }
}
