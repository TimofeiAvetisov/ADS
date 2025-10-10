#include <bits/stdc++.h>

using namespace std;

const long double eps = 1e-12;

struct point { 
    long long x, y;
};

long double dist(point i, point j) {
    return sqrtl((i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y));

}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<point> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    if (n == 2) {
        cout << 1 << ' ' << 2 << ' ' << 1 << '\n';
        return 0;
    }
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }


    vector<long double> dists(n * n);
    for (int i = 0; i < n; ++i) {
        dists[i * n + i] = 0.0;
        for (int j = i + 1; j < n; ++j) {
            long double d = dist(p[i], p[j]);
            dists[i * n + j] = d;
            dists[j * n + i] = d;
        }
    }
    /*for (int i = 0; i < dists.size(); ++i) {
        cout << dists[i] << ' ';
    }
    cout << '\n';*/

    vector<int> answer;
    answer.reserve(n);
    vector<char> used(n, 0);

    int cur = 0;
    used[cur] = true;
    answer.push_back(cur);

    for (int i = 1; i < n; i++) {
        int ind = -1;
        long double ans = 1e30;
        for (int v = 0; v < n; v++) {
            if (!used[v]) {
                if (dists[cur * n + v] < ans) {
                    ans = dists[cur * n + v];
                    ind = v;
                }
            }
        }
        cur = ind;
        used[cur] = true;
        answer.push_back(cur);
    }

    int k = 500; //<---------- можно менять
    vector<vector<int>> knn(n);
    vector<pair<long double, int>> tmp;
    for (int i = 0; i < n; ++i) {
        tmp.clear();
        tmp.reserve(n - 1);
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }

            tmp.emplace_back(dists[i * n + j], j);
        }

        sort(tmp.begin(), tmp.end());
        knn[i].reserve(min(k, (int)tmp.size()));

        for (int v = 0; v < min(k, (int)tmp.size()); ++v) {
            knn[i].push_back(tmp[v].second);
        }
    }

    vector<int> index(n);
    for (int i = 0; i < n; ++i) {
        index[answer[i]] = i;
    }

    bool flag = true;
    int iter = 0;
    while (flag) { // <-----------------можно менять
        flag = false;
        for (int i = 0; i < n; ++i) {
            index[answer[i]] = i;
        }

        for (int i = 0; i < n && !flag; ++i) {
            int v = answer[i];
            int u = answer[(i + 1) % n];
            for (int x : knn[v]) {
                int y = answer[(index[x] + 1) % n];
                if (v == x || v == y || u == x || u == y) {
                    continue;
                }
                if (dists[v * n + u] + dists[x * n + y] - dists[v * n + x] - dists[u * n + y] > eps) {
                    if (index[u] < index[x]) {
                        reverse(answer.begin() + index[u], answer.begin() + index[x] + 1);
                    } else {
                        reverse(answer.begin() + index[u], answer.end());
                        reverse(answer.begin(), answer.begin() + index[x] + 1);
                        reverse(answer.begin(), answer.end());
                    }
                    flag = true;
                    break;
                }
            }
        }
    }

    rotate(answer.begin(), find(answer.begin(), answer.end(), 0), answer.end());

    for (auto v : answer) {
        cout << v + 1 << ' ';
    }
    cout << 1 << '\n';
}

