#include <bits/stdc++.h>
using namespace std;

// ----- persistent segtree (array-based) -----
static const int MAXN = 100000;
static const int MAXVERT = 4200000; // ~ 2 * n * log2(n) + build margin

int sumv[MAXVERT], L[MAXVERT], R[MAXVERT];
int root[MAXN + 5];
int nodes = 0;

int build(int tl, int tr) {
    int v = ++nodes;
    sumv[v] = 0;
    if (tl + 1 < tr) {
        int tm = (tl + tr) >> 1;
        L[v] = build(tl, tm);
        R[v] = build(tm, tr);
    }
    return v;
}

int update(int v, int tl, int tr, int pos, int val) {
    int nv = ++nodes;
    L[nv] = L[v]; R[nv] = R[v]; sumv[nv] = sumv[v];
    if (tl + 1 == tr) { sumv[nv] = val; return nv; }
    int tm = (tl + tr) >> 1;
    if (pos < tm) L[nv] = update(L[v], tl, tm, pos, val);
    else          R[nv] = update(R[v], tm, tr, pos, val);
    sumv[nv] = sumv[L[nv]] + sumv[R[nv]];
    return nv;
}

int query(int v, int tl, int tr, int l, int r) { // [l, r)
    if (r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r) return sumv[v];
    int tm = (tl + tr) >> 1;
    return query(L[v], tl, tm, l, r) + query(R[v], tm, tr, l, r);
}

// ----- main -----
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // build all versions root[r]
    root[0] = build(1, n + 1);
    vector<int> last(m + 1, 0); // last position for each server id in [1..m]
    for (int i = 1; i <= n; ++i) {
        int cur = root[i - 1];
        int val = a[i];               // 1..m
        if (last[val]) cur = update(cur, 1, n + 1, last[val], 0);
        cur = update(cur, 1, n + 1, i, 1);
        root[i] = cur;
        last[val] = i;
    }

    int q; cin >> q;
    int p = 0; // previous answer r
    while (q--) {
        int xi, yi; cin >> xi >> yi;
        int l = ((xi + p) % n) + 1;
        int k = ((yi + p) % m) + 1;
        // быстрая проверка достижимости
        int maxDistinct = query(root[n], 1, n + 1, l, n + 1);
        if (k > maxDistinct) { cout << 0 << '\n'; p = 0; continue; }

        int lo = l, hi = n, ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            int cnt = query(root[mid], 1, n + 1, l, mid + 1);
            if (cnt >= k) { ans = mid; hi = mid - 1; }
            else lo = mid + 1;
        }
        cout << ans << '\n';
        p = ans;
    }
    return 0;
}
