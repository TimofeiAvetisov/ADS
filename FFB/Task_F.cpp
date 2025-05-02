#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = INT_MAX;
const int MAXN = 100;

//Если я вылечу по памяти, то вылечу сразу(надеюсь)
int tr[MAXN][MAXN];
int16_t nxt[MAXN][MAXN], flights[MAXN][MAXN];
bool infinite[MAXN][MAXN];

signed main(){
    int n, m, k;
    cin >> n >> m >> k;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            tr[i][j] = (i == j ? 0 : INF);
            nxt[i][j] = -1;
            flights[i][j] = -1;
        }
    }

    for(int i = 0;i < m; ++i){
        int u, v, q;
        cin >> u >> v >> q;
        --u;--v;
        q = -q;
        if(tr[u][v] > q){
            tr[u][v] = q;
            nxt[u][v] = v;
            flights[u][v] = i + 1;
        }
    }

    for(int p = 0; p < n; ++p){
        for(int u = 0; u < n; ++u) {
            if(tr[u][p] != INF) {
                for(int v = 0; v < n; ++v) {
                    if(tr[p][v] != INF) {
                        if(tr[u][v] > tr[u][p] + tr[p][v]){
                            tr[u][v] = tr[u][p] + tr[p][v];
                            nxt[u][v] = nxt[u][p];
                        }
                    }
                }   
            }
        }
    }

    for(int u = 0; u < n; ++u){
        for(int v = 0; v < n; ++v){
            infinite[u][v] = false;
            for(int p = 0; p < n; ++p){
                if(tr[p][p] < 0 && tr[u][p] != INF && tr[p][v] != INF){
                    infinite[u][v] = true;
                    break;
                }
            }
        }
    }

    vector<int> a(k);
    for(int i = 0; i < k; ++i){
        cin >> a[i];
        --a[i];
    }

    for(int i = 0; i < k - 1; ++i){
        if(infinite[a[i]][a[i+1]]){
            cout << "infinitely kind";
            return 0;
        }
    }

    int ans = 0;
    for(int i = 0; i < k - 1; ++i){
        int u = a[i], v = a[i + 1];
        int tmp = u;
        while(tmp != v){
            ++ans;
            tmp = nxt[tmp][v];
        }
    }

    cout << ans << "\n";
    for(int i = 0; i < k - 1; ++i){
        int u = a[i], v = a[i + 1];
        int tmp = u;
        while(tmp != v){
            cout << flights[tmp][nxt[tmp][v]] << ' ';
            tmp = nxt[tmp][v];
        }
    }
}
