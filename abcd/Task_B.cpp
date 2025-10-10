#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int MAXVERT = 4000000; // лог меменьше 20, ну еще с барского плеча накину 

int value[MAXVERT], left_ch[MAXVERT], right_ch[MAXVERT];
int root[MAXN + 10];
int nodes = 0;

vector<int> value;

// v - вершина
// value[v] = val
// left_ch[v] = k
// right_ch[v] = t
// root[r] = root_ind
// left_ch[root[r]]

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
    }else {
        right_ch[u] = update(right_ch[u], m, r, pos, val);
    }
    value[u] = value[left_ch[u]] + value[right_ch[u]];
    return u;
}

int query(int v, int ql, int qr, int l, int r) {
    if (r <= ql || qr <= l){ 
        return 0;
    }
    if (l <= ql && qr <= r) {
        return value[v];
    }
    return query(left_ch[v], ql, (ql + qr) / 2, l, r) + query(right_ch[v], (ql + qr) / 2, qr, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    root[0] = build(1, n + 1);
    vector<int> used(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int cur = root[i - 1];
        int val = a[i];
        if (used[val]) {
            cur = update(cur, 1, n + 1, used[val], 0);
        }
        cur = update(cur, 1, n + 1, i, 1);
        root[i] = cur; //tree_i
        used[val] = i; // val -> i
    }

    int q;
    cin >> q;
    int p = 0;

    for (int querry = 0; querry < q; ++querry) {
        int x, y;
        cin >> x >> y;
        int l = ((x + p) % n) + 1;
        int k = ((y + p) % m) + 1;

        int maxx = query(root[n], 1, n + 1, l, n + 1);
        if (k > maxx) {
            cout << 0 << '\n';
            p = 0;
            continue;
        }

        int left = l, right = n, ans = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            int cur_ans = query(root[mid], 1, n + 1, l, mid + 1);
            if (cur_ans >= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        cout << ans << '\n';
        p = ans;
    }
}
