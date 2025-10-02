#include <bits/stdc++.h>

using namespace std;

void pack(const string &s) {
    unordered_map<string, int> d;
    for (int i = 0; i < 26; ++i) {
        string ch(1, char('a' + i));
        d[ch] = i;
    }
    int sz = 26;

    vector<int> answer;
    string tmp = "";
    for (auto c : s) {
        string temp = tmp + c;
        //cout << tmp << ' ' << temp << ' ' << c << '\n';
        if (d.count(temp)) {
            tmp = temp;
        } else {
            answer.push_back(d[tmp]);
            if (sz < 256) {
                d[temp] = sz++;
            } else {
                d.clear();
                for (int i = 0; i < 26; ++i) {
                    string ch(1, char('a' + i));
                    d[ch] = i;
                }
                sz = 26;
                d[string(1, c)] = sz++;
            }
            tmp = string(1, c);
        }
    }

    if (!tmp.empty()) {
        answer.push_back(d[tmp]);
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i] << ' ';
    }
}

void unpack(int n, const vector<int> &c) {
    vector<string> d;
    for (int i = 0; i < 26; ++i) {
        string ch(1, char('a' + i));
        d.push_back(ch);
    }
    int sz = 26;
    string tmp = d[c[0]];
    cout << tmp;
    for (int i = 1; i < n; ++i) {
        int k = c[i];
        string temp;
        if (k < sz) {
            temp = d[k];
        } else if(k == sz && sz < 256){
            temp = tmp + tmp[0];
        }

        cout << temp;
        if (sz < 256) {
            d.push_back(tmp + temp[0]);
            ++sz;
        } else {
            d.clear();
            for (int j = 0; j < 26; ++j) {
                string ch(1, char('a' + j));
                d.push_back(ch);
            }
            sz = 26;
        }

        tmp = temp;
    }

}

int main() {

    string cmd;
    cin >> cmd;

    if (cmd == "pack") {
        string s;
        cin >> s;
        pack(s);
        cout << '\n';
        cout.flush();
    } else {
        int n;
        cin >> n;
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
        }
        unpack(n, c);
        cout << '\n';
        cout.flush();
    }
}