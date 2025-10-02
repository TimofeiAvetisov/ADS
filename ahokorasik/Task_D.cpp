#include <bits/stdc++.h>

using namespace std;

const int k = 26;
vector<string> words;

struct Node {
    Node *to[k], *next[k], *link, *term;
    bool is_terminal;

    vector<int> out;

    Node() {
        fill(begin(to), end(to), nullptr);
        fill(begin(next), end(next), nullptr);
        link = nullptr;
        term = nullptr;
        is_terminal = false;
    }
};

Node *root = new Node();

void add_string(const string &s, const int id) {
    Node* cur = root;
    for (char c : s) {
        int ind = c - 'a';
        if (!cur->to[ind]) {
            cur->to[ind] = new Node();
        }
        cur = cur->to[ind];
    }

    cur->is_terminal = true;
    cur->out.push_back(id);
}

void build() {
    queue<Node*> q;
    root->link = root;
    root->term = nullptr;

    for (int c = 0; c < k; ++c) {
        if (root->to[c]) {
            root->next[c] = root->to[c];
            root->to[c]->link = root;
            root->to[c]->term = nullptr;
            q.push(root->to[c]);
        } else {
            root->next[c] = root;
        }
    }

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();

        for (int c = 0; c < k; ++c) {
            if (cur->to[c]) {
                Node* next_node = cur->to[c];
                cur->next[c] = next_node;
                //must have
                next_node->link = cur->link->next[c];

                //must have
                if (next_node->link->is_terminal) {
                    next_node->term = next_node->link;
                } else {
                    next_node->term = next_node->link->term;
                }
                //next_node->term = (next_node->link->is_terminal ? next_node->link : next_node->link->term);

                q.push(next_node);
            } else {
                cur->next[c] = cur->link->next[c];
            }
        }
    }
}

void query(const string &s) {
    Node* cur = root;
    unordered_map<int, vector<int>> answer;
    for (int i = 0; i < s.size(); ++i) {
        auto c = s[i];
        int ind = c - 'a';
        cur = cur->next[ind];

        for (Node* tmp = cur; tmp != nullptr; tmp = tmp->term) {
            for (int x : tmp->out) {
                answer[x].push_back(i - words[x].size() + 2);
            }
        }
    }


    for (int i = 0; i < words.size(); ++i) {
        cout << answer[i].size() << ' ';
        for (auto num : answer[i]) {
            cout << num << ' ';
        }
        cout << '\n';
    }
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    int n;
    cin >> n;
    words.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    for (int i = 0; i < n; ++i) {
        add_string(words[i], i);
    }
    build();

    query(s);
    
}