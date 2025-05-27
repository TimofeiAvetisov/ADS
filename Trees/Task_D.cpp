#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, cnt;
    Node *left, *right;

    Node(int val) : val(val), cnt(1), left(nullptr), right(nullptr) {}
};

Node* add_node(int tmp, Node *cur) {
    if (!cur) return new Node(tmp);

    if(tmp == cur->val) {
        cur->cnt++;
    }

    if (tmp < cur->val)
        cur->left = add_node(tmp, cur->left);
    if (tmp > cur->val)
        cur->right = add_node(tmp, cur->right);
    return cur;
}

void deadend(Node* root) {
    if (!root) {
        return;
    }

    deadend(root->left);
    cout << root->val << ' ' <<  root->cnt << '\n';
    deadend(root->right);
}

int main() {
    Node* root = nullptr;

    int tmp;
    cin >> tmp;
    while (tmp != 0) {
        root = add_node(tmp, root);
        cin >> tmp;
    }

    deadend(root);
}
