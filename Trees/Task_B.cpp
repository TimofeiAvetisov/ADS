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



void sorted(Node* root) {
    if (!root) return;

    sorted(root->left);
    cout << root->val << '\n';
    sorted(root->right);
}

Node *root;

int main() {

    int tmp;
    cin >> tmp;

    while (tmp != 0) {
        root = add_node(tmp, root);
        cin >> tmp;
    }

    sorted(root);

}