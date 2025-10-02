/*#include <bits/stdc++.h>

using namespace std;

const int k = 26;

struct Node {
    vector<Node*> children;
    int cnt;
    int terminal;
    Node() : children(26, nullptr), cnt(0), terminal(0) {}
};


void add_string(const string &s, Node *root) {
    Node *cur = root;
    for (auto ch : s) {
        cur->cnt += 1;
        int c = ch - 'a';
        if (!cur->children[c]) {
            cur->children[c] = new Node();
        }

        cur = cur->children[c];
    }

    cur->terminal += 1;
    cur->cnt += 1;
}

void search(int n, Node *root) {
    Node *cur = root;
    string answer = "";

    while (n > cur->terminal) {
        for (int c = 0; c < k; ++c) {
            if (!cur->children[c]) {
                continue;
            }
            Node *next_node = cur->children[c];
            if (next_node->cnt < n) {
                n -= next_node->cnt;
            } else {
                answer += (char)(c + 'a');
                cur = next_node;
                break;
            }
        }
    }
    cout << answer << '\n';
}

Node *root = new Node();
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            string s;
            cin >> s;
            add_string(s, root);
        } else {
            int p;
            cin >> p;
            search(p, root);
        }
    }    
}*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<int> children;
    int cnt;
    int terminal;
    Node() : children(26, -1), cnt(0), terminal(0) {}
};
const int k = 26;
vector<Node> bor;

void add_string(const string &s) {
    int v = 0;
    for (auto ch : s) {
        int c = (ch - 'a');
        bor[v].cnt += 1;
        if (bor[v].children[c] == -1) {
            bor.emplace_back();
            bor[v].children[c] = bor.size() - 1;
        }
        v = bor[v].children[c];
    }

    bor[v].terminal += 1;
    bor[v].cnt += 1;
}

void search(int n) {
    int v = 0;
    string answer = "";
    while (n > bor[v].terminal) {
        for (int c = 0; c < k; ++c) {
            int child = bor[v].children[c];
            if (child == -1) {
                continue;
            }

            if (n > bor[child].cnt) {
                n -= bor[child].cnt;
            } else {
                answer += (char)(c + 'a');
                v = child;
                break;
            }
        }
    }

    cout << answer << '\n';
}


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    bor.emplace_back();

    i
}