#include <bits/stdc++.h>

using namespace std;

vector<set<int>> g;
vector<int> robots;
vector<vector<pair<int, int>>> dist;
int n, k, m;

int get_min_dist(int a, int b) {
    if (a == -1 && b == -1) return -1;
    
    if (a == -1) return b;
    if (b == -1) return a;
    
    return min(a, b);
}

void bfs(int i) {
    vector<int> q(4 * n);
    int start = 0, end = 1;
    q[0] = robots[i];
    dist[i][robots[i]].second = 0;

    while(end != start) {
        int v = q[start++];
        for (auto u : g[v]) {
            if (dist[i][u].first == -1) {
                if (dist[i][v].second != -1) {
                    dist[i][u].first = dist[i][v].second + 1;
                    q[end++] = u;
                }
            } else {
                if (dist[i][v].second != -1) {
                    if (dist[i][u].first > dist[i][v].second + 1) {
                        dist[i][u].first = dist[i][v].second + 1;
                        q[end++] = u;
                    }
                }
            }

            if (dist[i][u].second == -1) {
                if (dist[i][v].first != -1) {
                    dist[i][u].second = dist[i][v].first + 1;
                    q[end++] = u;
                }
            } else {
                if (dist[i][v].first != -1) {
                    if (dist[i][u].second > dist[i][v].first + 1) {
                        dist[i][u].second = dist[i][v].first + 1;
                        q[end++] = u;
                    }
                }
            }
        }
    }
}

int main() {
    cin >> n;
    g.resize(n);
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;

        g[v].insert(u);
        g[u].insert(v);
    }

    cin >> m;
    robots.resize(m);
    dist.resize(m, vector<pair<int, int>>(n, make_pair(-1, -1)));
    for (int i = 0; i < m; ++i) {
        int u;
        cin >> u;
        --u;
        robots[i] = u;
    }

    for (int i = 0; i < m; ++i) {
        bfs(i);
    }

    if (m == 1) {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        if (dist[0][robots[i]].first == -1 && dist[0][robots[i]].second == -1) {
            cout << -1;
            return 0;
        }
    }

    vector<pair<int, int>> point_answer_pair(n, {-2, -2});
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (point_answer_pair[i].first == point_answer_pair[i].second == -1) break;
            if (point_answer_pair[i].first != -1) {
                if (dist[j][i].first == -1) {
                    point_answer_pair[i].first = -1;
                }  else {
                    if(point_answer_pair[i].first == -2) {
                        point_answer_pair[i].first = dist[j][i].first; 
                    } else {
                        point_answer_pair[i].first = max(dist[j][i].first, point_answer_pair[i].first);
                    }
                }
            }

            if (point_answer_pair[i].second != -1) {
                if (dist[j][i].second == -1) {
                    point_answer_pair[i].second = -1;
                }  else {
                    if(point_answer_pair[i].second == -2) {
                        point_answer_pair[i].second = dist[j][i].second; 
                    } else {
                        point_answer_pair[i].second = max(dist[j][i].second, point_answer_pair[i].second);
                    }
                }
            }
        }
    }

    vector<int> point_answer(n, -1);
    for (int i = 0; i < n; ++i) {
        if (point_answer_pair[i].first == point_answer_pair[i].second == -1) {
            point_answer[i] = -1;
            continue;
        }
        if (point_answer_pair[i].first != -1) {
            point_answer[i] = point_answer_pair[i].first;
        }
        if (point_answer_pair[i].second != -1) {
            point_answer[i] = min(point_answer[i], point_answer_pair[i].second);
        }
    }

    int edge_answer = -1;
    for (int v = 0; v < n; ++v) {
        for (auto u : g[v]) {
            if (u > v) {
                continue;
            }
            int d = -1;
            bool flag = false;
            //edge {v, u};
            for (int i = 0; i < m; ++i) {
                int cur_dist = get_min_dist(dist[i][u].first, dist[i][u].second);
                int cur_dist_h = get_min_dist(dist[i][v].first, dist[i][v].second);
                cur_dist = get_min_dist(cur_dist, cur_dist_h);
                //cout << "MIN_DIST FROM " << robots[i] << " TO " << "(" << u << ", " << v << ") IS " << cur_dist << '\n';  
                if (cur_dist == -1) {

                }
                if (d != -1) {
                    flag = (flag || (abs(d - cur_dist) % 2 == 1));
                }
                d = max(d, cur_dist);
            }
            if (flag) {
                //cout << "(" << u << ", " << v << ") " << d + 0.5 << '\n';
                if (edge_answer == -1) {
                    edge_answer = d;
                } else {
                    edge_answer = min(edge_answer, d);
                }
            }
        }
    }
    float answer = 0;
    if (edge_answer != -1) {
        answer = edge_answer + 0.5;
    } else {
        answer = 1e9;
    }
    for (auto pa : point_answer) {
        if (pa != -1) {
            answer = min((float)pa, answer);
        }
    }

    cout << answer << '\n';

    /*
    for (auto q : dist) {
        for (auto [a, b] : q) {
            cout << "(" << a << ' ' << b << ")\t";
        }
        cout << '\n';
    }
    cout << '\n';
    for (auto [a, b]: point_answer_pair) {
        cout << "(" << a << ' ' << b << ") ";
    }
    cout << '\n';

    for (auto a : point_answer) {
        cout << a << ' ';
    }
    cout << '\n';
    */
}