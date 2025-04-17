#include <bits/stdc++.h>
using namespace std;

vector<tuple<int,int,int>> gen_states(tuple<int,int,int>& c, const vector<int>& cap) {
    auto [x,y,z] = c;
    vector<tuple<int,int,int>> r;
    
    r.push_back({cap[0], y, z});
    r.push_back({x, cap[1], z});
    r.push_back({x, y, cap[2]});
    
    r.push_back({0, y, z});
    r.push_back({x, 0, z});
    r.push_back({x, y, 0});
    
    auto p = [&](int f, int t) {
        int a[] = {x,y,z};
        int d = min(a[f], cap[t]-a[t]);
        a[f] -= d;
        a[t] += d;
        return make_tuple(a[0], a[1], a[2]);
    };
    
    r.push_back(p(0,1));
    r.push_back(p(0,2));
    r.push_back(p(1,0));
    r.push_back(p(1,2));
    r.push_back(p(2,0));
    r.push_back(p(2,1));
    
    return r;
}

int main() {
    vector<int> cap(3);
    int v;
    cin >> cap[0] >> cap[1] >> cap[2] >> v;
    
    int g = __gcd(cap[0], __gcd(cap[1], cap[2]));
    if(v % g != 0) {
        cout << -1;
        return 0;
    }
    
    queue<tuple<int,int,int>> q;
    map<tuple<int,int,int>, int> d;
    q.push({0,0,0});
    d[{0,0,0}] = 0;
    
    while(!q.empty()) {
        auto c = q.front();
        q.pop();
        
        auto [x,y,z] = c;
        if(x == v || y == v || z == v) {
            cout << d[c];
            return 0;
        }
        
        for(auto& s : gen_states(c, cap)) {
            if(!d.count(s)) {
                d[s] = d[c] + 1;
                q.push(s);
            }
        }
    }
    
    cout << -1;
}