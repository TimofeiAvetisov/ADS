#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

long long LOG;

bool anc(long long vertex1, long long vertex2, vector<long long> &first, vector<long long> &last) {
    return ((first[vertex1] <= first[vertex2]) and (last[vertex1] >= last[vertex2]));
}

void dfs(pair<int, int> now, vector<vector<pair<int, int>>> &g, vector<bool> &v, vector<long long> &first,
    vector<long long> &last,
    long long &cnt,
    vector<vector<long long>> &up, vector<vector<long long>> &e) {
    for (long long l = 0; l < LOG - 1; l++) {
        up[now.first][l + 1] = up[up[now.first][l]][l];
        e[now.first][l + 1] = min(e[now.first][l], e[up[now.first][l]][l]);
    }
    v[now.first] = true;
    first[now.first] = cnt += 1;
    for (auto neig: g[now.first])
        if (!v[neig.first]) {
            up[neig.first][0] = now.first;
            e[neig.first][0] = neig.second;
            dfs(neig, g, v, first, last, cnt, up, e);
        }
    last[now.first] = cnt += 1;
}


long long lca(long long vertex1, long long vertex2, vector<long long> &first, vector<long long> &last,
              vector<vector<long long>> &up, vector<vector<long long>> &e) {
    long long mn = 100000; 
    if (anc(vertex2, vertex1, first, last))
        swap(vertex2, vertex1);
    for (long long l = LOG; l > 0; l--)
        if (not anc(up[vertex2][l - 1], vertex1, first, last)) {
            mn = min(mn, e[vertex2][l - 1]);
            vertex2 = up[vertex2][l - 1];
        }
    return min(mn, e[vertex2][0]);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long vertex_count, q, vertex1, vertex2, root, a, b, x, y, z, weight;
    cin >> vertex_count;
    LOG = 29;
    vector<vector<pair<int, int>>> graph(vertex_count);
    vector<vector<long long>> up(vertex_count, vector<long long>(29));
    vector<vector<long long>> edge(vertex_count, vector<long long>(29, 1e9));
    for (long long i = 1; i < vertex_count; i++) {
        cin >> vertex1 >> weight;
        graph[vertex1 - 1].emplace_back(i, weight);
    }
    
    vector<bool> visited(vertex_count);
    cin >> q;
    vector<long long> first(vertex_count);
    vector<long long> last(vertex_count);
    long long k = 0;
    dfs(make_pair(0, 1e9), graph, visited, first, last, k, up, edge);
//    for (auto el: first) {
//        cout << el << " ";
//    }
//    cout << endl;
//    for (auto el: last) {
//        cout << el << " ";
//    }
//    cout << endl;

    for (int i = 0; i < q; ++i) {
        cin >> vertex1 >> vertex2;
        --vertex1;--vertex2;
        cout << min(lca(vertex1, vertex2, first, last, up, edge), lca(vertex2, vertex1, first, last, up, edge)) << endl;
    }

    
}

//   0
//  1 2
// 3   5  4