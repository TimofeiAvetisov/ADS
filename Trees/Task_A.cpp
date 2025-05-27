#include <bits/stdc++.h>

using namespace std;

int answer = 0;

struct Node{
    int val;

    Node* left, *right;

    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

Node* add_node(int tmp, Node *cur, int d) {
    if (!cur) {
        answer = max(answer, d);
        return new Node(tmp);
    }

    if (tmp < cur->val) {
        cur->left = add_node(tmp, cur->left, d + 1);
    }
    
    if (tmp > cur->val) {
        cur->right = add_node(tmp, cur->right, d + 1);
    }

    return cur;
}

Node *root;

int main() {

    int tmp;
    cin >> tmp;

    while (tmp != 0) {
        root = add_node(tmp, root, 1);
        cin >> tmp;
    }


    cout << answer << '\n';
}