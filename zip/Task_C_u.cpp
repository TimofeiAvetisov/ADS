#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>


using namespace std;

vector<unsigned char> pack_codes(const vector<int> &a) {
    vector<unsigned char> b;
    unsigned buf = 0;
    int bit = 0;
    int bits = 5;
    int nxt = 26;

    for (int x: a) {
        buf |= (unsigned(x) & ((1u << bits) - 1)) << bit;
        bit += bits;
        while (bit >= 8) {
            b.push_back((unsigned char) (buf & 255));
            buf >>= 8;
            bit -= 8;
        }
        nxt++;
        if (nxt == (1 << bits) && bits < 16) bits++;
    }
    if (bit > 0) b.push_back((unsigned char) (buf & 255));
    return b;
}

vector<int> unpack_codes(const vector<unsigned char> &b) {
    vector<int> a;
    unsigned buf = 0;
    int bit = 0;
    int bits = 5;
    int nxt = 26;
    int i = 0;

    while (true) {
        while (bit < bits) {
            if (i >= (int) b.size()) return a;
            buf |= (unsigned) b[i++] << bit;
            bit += 8;
        }
        unsigned val = buf & ((1u << bits) - 1);
        buf >>= bits;
        bit -= bits;
        a.push_back((int) val);
        nxt++;
        if (nxt == (1 << bits) && bits < 16) bits++;
    }
}


map<string, int> alphabet;
map<int, string> revalphabet;

//abdabccabcdab

vector<int> encode(string s) {
    vector<int> ans;
    int cnt = 26;
    int pos = 0, len = 1;
    int last;
    while (pos + len <= s.size()) {
        string sub = s.substr(pos, len);
        if (alphabet.count(sub)) {
            len++;
            last = alphabet[sub];
        } else {
            alphabet[sub] = cnt;
            cnt++;
            pos += len - 1;
            len = 1;
            ans.push_back(last);
        }
    }
    ans.push_back(last);
    return ans;
}

string decode(vector<int> code) {
    string ans = revalphabet[code[0]];
    string last, tmp;
    int cnt = 26;


    for (int i = 1; i < code.size(); i++) {
        if (revalphabet.count(code[i])) {
            tmp = revalphabet[code[i]];
        } else if (code[i] == cnt) {
            last = revalphabet[code[i - 1]];
            tmp = last + last[0];
        }
        ans += tmp;
        revalphabet[cnt] = revalphabet[code[i - 1]] + tmp[0];
        cnt++;
    }

    return ans;

}


signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);


    for (char c = 'a'; c <= 'z'; c++) {
        alphabet[string(1, c)] = c - 'a';
    }
    for (char c = 'a'; c <= 'z'; c++) {
        revalphabet[c - 'a'] = string(1, c);
    }

    string n;
    cin >> n;
    string x;
    if (n == "pack") {
        cin >> x;
        vector<int> codes = encode(x);
        vector<uint8_t> bytes = pack_codes(codes);
        cout << bytes.size() << "\n";
        for (size_t i = 0; i < bytes.size(); i++) {
            cout << int(bytes[i]);
            if (i + 1 == bytes.size()) {
                cout << '\n';
            } else {
                cout << ' ';
            }
        }
    }
    if (n == "unpack") {
        int sz;
        cin >> sz;
        vector<uint8_t> bytes(sz);
        for (int i = 0; i < sz; i++) {
            int t;
            cin >> t;
            bytes[i] = uint8_t(t);
        }
        vector<int> codes = unpack_codes(bytes);
        cout << decode(codes) << '\n';
    }
}

//11011101001

//010010100
//010110100

//0101010100101010101010010101010
