#include <bits/stdc++.h>
#include <ranges>

using namespace std;

struct Node {
    vector<Node*> children;
    bool is_terminal;
    int cnt;
    int end_here;

    Node() : children(26, nullptr), is_terminal(false), cnt(0), end_here(0) {}
};

void add_word_to_trie(Node* cur, string word, int ind) {
    cur->cnt += 1;
    if (ind == word.size()) {
        cur->is_terminal = true;
        cur->end_here += 1;
        return;
    }

    int index = (int)word[ind] - 'a';
    if (!cur->children[index]) {
        cur->children[index] = new Node();
    }

    add_word_to_trie(cur->children[index], word, ind + 1);
}


void find_word(Node* cur, int& num, string& ans) {
    if (cur->is_terminal) {
        num -= cur->end_here;
        if (num <= 0) return;
    }

    for (int i = 0; i < 26; ++i) {
        if (cur->children[i]) {
            if (cur->children[i]->cnt < num) {
                num -= cur->children[i]->cnt;
            } else {
                ans.push_back('a' + i);
                find_word(cur->children[i], num, ans);
                return;
            }
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Node* root = new Node();

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            string word;
            cin >> word;
            add_word_to_trie(root, word, 0);
            continue;
        }

        int num;
        cin >> num;
        string ans = "";
        find_word(root, num, ans);
        cout << ans << '\n';
    }
    
}

string search(int n) {
    int vertex = 0;
    string ans = "";
    while (n > 0) {
        for (int c = 0; c < alphb; c++) {
            int descendant = trie[vertex].descendants[c];
            if (descendant == -1) {
                continue;
            }

            if (n > trie[descendant].temrminal_cnt) {
                n -= trie[descendant].temrminal_cnt;
            } else {
                ans += char(c + 'a');
                vertex = descendant;
                break;
            }
        }
    }

    return ans;
}