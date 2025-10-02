#include <bits/stdc++.h>

using namespace std;



struct Node {
    vector<Node*> children;
    bool is_new;

    Node() : children(26, nullptr), is_new(true) {}
};

vector<Node*> nodes;
int current = 1;

bool add_word_to_trie(Node* cur, char c) {
    int ind = int(c) - 'a';
    if (!cur->children[ind]) {
        cur->children[ind] = new Node();
    }
    cur = cur->children[ind];
    nodes[current] = cur;
    current++;
    if (!cur->is_new) {
        return false;
    }
    cur->is_new = false;
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    nodes.resize(n + 1, nullptr);
    Node* root = new Node();
    nodes[0] = root;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        char c;
        cin >> c;
        ans += add_word_to_trie(nodes[p], c);
        cout << ans << '\n';
    }


    
}