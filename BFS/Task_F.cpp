#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    unordered_map<int, vector<int>> lanes;
    unordered_map<int, vector<int>> stations;

    for (int i = 0; i < m; ++i) {
        int tmp;
        cin >> tmp;
        for (int j = 0; j < tmp; ++j) {
            int st;
            cin >> st;
            --st;
            lanes[i].push_back(st);
            stations[st].push_back(i);
        }
    }

    int a, b;
    cin >> a >> b;
    --a;--b;

    vector<int> l_dist(m, -1);
    for (auto l : stations[a]) {
        l_dist[l] = 0;
    }

    vector<vector<int>> g(m);

    vector<int> q(2 * (n + m));
    int start = 0, end = 0;
    for (int i = 0; i < m; ++i) {
        if (l_dist[i] == 0) {
            q[end] = i;
            end++;
        }
    }

    while (start != end) {
        int lane = q[start];
        ++start;
        for (auto st : lanes[lane]) {
            for (auto ln : stations[st]) {
                if (l_dist[ln] == -1|| l_dist[ln] > l_dist[lane] + 1) {
                    q[end] = ln;
                    end++;
                    l_dist[ln] = l_dist[lane] + 1;
                }
            }
        }  
    }
    int answer = -1;
    for (auto ln : stations[b]) {
        if ((answer == -1 && l_dist[ln] != -1) || (answer > l_dist[ln])) {
            answer = l_dist[ln];
        }
    }

    cout << answer;
}