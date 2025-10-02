#include <bits/stdc++.h>

using namespace std;

struct Node{
    int val;

    Node* left, *right;

    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

Node* add_node(int tmp, Node *cur) {
    if (!cur) {
        return new Node(tmp);
    }

    if (tmp < cur->val) {
        cur->left = add_node(tmp, cur->left);
    }
    
    if (tmp > cur->val) {
        cur->right = add_node(tmp, cur->right);
    }

    return cur;
}

void print_tree(Node *root) {
    queue<Node*> q;

    q.push(root);

    while(!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (!cur) {
            continue;
        }
        cout << cur->val << ' ';
        q.push(cur->left); q.push(cur->right);
    }
}

Node* root;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        root = add_node(a[i], root);
    }

    print_tree(root);
}