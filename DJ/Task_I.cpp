#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double INF = 1e18;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<double> t(n), v(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i] >> v[i];
    }

    vector<vector<pair<int, double>>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        double w;
        cin >> a >> b >> w;
        --a; --b;
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }

    vector<double> d(n * n, INF);
    vector<int> pr(n * n, -1), vis(n * n);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    for (int m = 0; m < n; ++m) {
        d[m * n + m] = t[m]; // Время подготовки саней в городе m
        q.push({d[m * n + m], m * n + m});
    }

    while (!q.empty()) {
        auto [dist, u] = q.top(); q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        int city = u / n;
        int src = u % n;

        for (auto [to, wgt] : g[city]) {
            double cost = wgt / v[src];
            int uid = to * n + src;
            if (d[uid] > dist + cost) {
                d[uid] = dist + cost;
                pr[uid] = u;
                q.push({d[uid], uid});
            }
        }

        // Пересадка в текущем городе
        for (int ns = 0; ns < n; ++ns) {
            if (ns == city) continue;
            int uid = city * n + ns;
            double cost = t[city]; // Время подготовки новых саней
            if (d[uid] > dist + cost) {
                d[uid] = dist + cost;
                pr[uid] = u;
                q.push({d[uid], uid});
            }
        }
    }

    double ans = 0;
    int worst = 0;
    for (int i = 0; i < n; ++i) {
        double total = d[i]; // Город i, src = i (начальное состояние)
        if (total > ans) {
            ans = total;
            worst = i;
        }
    }
    cout << fixed << setprecision(6) << ans << '\n';

    // Восстановление пути
    vector<int> path;
    int cur = worst * n + worst;
    while (cur != -1) {
        int city = cur / n;
        int src = cur % n;
        path.push_back(city + 1);
        cur = pr[cur];
    }
    reverse(path.begin(), path.end());

    // Удаляем дубликаты подряд идущих городов
    vector<int> cleaned_path;
    cleaned_path.push_back(path[0]);
    for (size_t i = 1; i < path.size(); ++i) {
        if (path[i] != cleaned_path.back()) {
            cleaned_path.push_back(path[i]);
        }
    }

    for (auto x : cleaned_path) {
        cout << x << ' ';
    }
    cout << '\n';
}