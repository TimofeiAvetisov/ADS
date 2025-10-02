#include <bits/stdc++.h>

using namespace std;

const int k = 26;
vector<int> used;

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
                next_node->link = cur->link->next[c];

                next_node->term = (next_node->link->is_terminal ? next_node->link : next_node->link->term);

                q.push(next_node);
            } else {
                cur->next[c] = cur->link->next[c];
            }
        }
    }
}

int query(const string &s, const int id) {
    Node* cur = root;
    int count = 0;
    for (char c : s) {
        int ind = c - 'a';
        cur = cur->next[ind];

        for (Node* tmp = cur; tmp != nullptr; tmp = tmp->term) {
            for (int x : tmp->out) {
                if (x != id && used[x] != id) {
                    used[x] = id;
                    ++count;
                }
            }
        }
    }

    return count;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    std::vector<string> passwords(n);
    for (int i = 0; i < n; ++i) {
        cin >> passwords[i];
        add_string(passwords[i], i);
    }
    build();
    used.resize(n, -1);

    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        answer += query(passwords[i], i);
    }

    cout << answer << '\n';
}