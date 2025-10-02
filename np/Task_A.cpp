#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 64;

int v;
int s;
vector<unsigned long long> mask;
unsigned long long full_mask;

int build_clr(unsigned long long cand, array<int, MAX_V>& ord, array<int, MAX_V>& clr) {
    int m = 0;
    int c = 0;
    unsigned long long rem = cand;

    while (rem != 0ULL) {
        ++c;
        unsigned long long cur = rem;
        unsigned long long used = 0ULL;

        while (cur != 0ULL) {
            int vertex = __builtin_ctzll(cur);

            ord[m] = vertex;
            clr[m] = c;
            ++m;

            used |= (1ULL << vertex);

            cur &= ~((1ULL << vertex) | mask[vertex]);
        }

        rem &= ~used;
    }

    return m;
}


bool solve(unsigned long long cand, int cur_sz) {
    if (cur_sz >= s) {
        return true;
    }
    if (cand == 0ULL) {
        return false;
    }

    array<int, MAX_V> ord{};
    array<int, MAX_V> clr{};
    int m = build_clr(cand, ord, clr);

    for (int i = m - 1; i >= 0; --i) {
        if (cur_sz + clr[i] < s) {
            return false;
        }

        int vertex = ord[i];
        if (solve(cand & mask[vertex], cur_sz + 1)) {
            return true;
        }

        cand &= ~(1ULL << vertex);
    }

    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> v >> s;

    int e;
    cin >> e;

    vector<unsigned long long> graph(v, 0ULL);
    for (int i = 0; i < e; ++i) {
        int a;
        int b;
        cin >> a >> b;
        --a;
        --b;

        graph[a] |= (1ULL << b);
        graph[b] |= (1ULL << a);
    }

    if (s == 0) {
        cout << "YES\n";
        return 0;
    }

    if (s > v) {
        cout << "NO\n";
        return 0;
    }

    full_mask = (v == MAX_V ? ~0ULL : ((1ULL << v) - 1ULL));

    mask.assign(MAX_V, 0ULL);
    for (int i = 0; i < v; ++i) {
        mask[i] = (~(graph[i] | (1ULL << i))) & full_mask;
    }

    if (solve(full_mask, 0)) {
        cout << "YES\n";
        return 0;
    }

    cout << "NO\n";
}
