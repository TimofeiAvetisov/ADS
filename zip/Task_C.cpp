#include <bits/stdc++.h>

using namespace std;


void pack(const string &s) {
    unordered_map<string,int> d;
    vector<string> rev(256);
    list<int> lru;
    vector<list<int>::iterator> pos(256);

    int sz = 0;
    for (int i = 0; i < 26; ++i) {
        string ch(1, 'a' + i);
        d[ch] = sz;
        rev[sz] = ch;
        lru.push_front(sz);
        pos[sz] = lru.begin();
        ++sz;
    }

    vector<int> ans;
    string tmp;
    for (char c : s) {
        string t = tmp + c;
        if (d.count(t)) {
            tmp = t;
            int k = d[t];
            lru.erase(pos[k]);
            lru.push_front(k);
            pos[k] = lru.begin();
        } else {
            ans.push_back(d[tmp]);
            if (sz < 256) {
                d[t] = sz;
                rev[sz] = t;
                lru.push_front(sz);
                pos[sz] = lru.begin();
                ++sz;
            } else {
                int old = lru.back();
                lru.pop_back();
                d.erase(rev[old]);
                d[t] = old;
                rev[old] = t;
                lru.push_front(old);
                pos[old] = lru.begin();
            }
            tmp = string(1, c);
        }
    }
    if (!tmp.empty()) {
        ans.push_back(d[tmp]);
    }

    cout << ans.size() << "\n";
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}

void unpack(int n, const vector<int> &c) {
    vector<string> d(256);
    list<int> lru;
    vector<list<int>::iterator> pos(256);

    int sz = 0;
    for (int i = 0; i < 26; ++i) {
        string ch(1, 'a' + i);
        d[sz] = ch;
        lru.push_front(sz);
        pos[sz] = lru.begin();
        ++sz;
    }

    string tmp = d[c[0]];
    cout << tmp;
    for (int i = 1; i < n; ++i) {
        int k = c[i];
        string temp;
        if (k < sz && !d[k].empty()) {
            temp = d[k];
        } else if (k == sz) {
            temp = tmp + tmp[0];
        }
        cout << temp;

        if (sz < 256) {
            d[sz] = tmp + temp[0];
            lru.push_front(sz);
            pos[sz] = lru.begin();
            ++sz;
        } else {
            int old = lru.back();
            lru.pop_back();
            d[old] = tmp + temp[0];
            lru.push_front(old);
            pos[old] = lru.begin();
        }
    
        lru.erase(pos[k]);
        lru.push_front(k);
        pos[k] = lru.begin();

        tmp = temp;
    }
    cout << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string cmd;
    cin >> cmd;
    if (cmd == "pack") {
        string s;
        cin >> s;
        pack(s);
    } else {
        int n;
        cin >> n;
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
        }
        unpack(n, c);
    }
}
