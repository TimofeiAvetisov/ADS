#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, clr;
    Node *left, *right;

    Node(int val, int clr) : val(val), clr(clr), left(nullptr), right(nullptr) {}
};
/*
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
*/

int main() {
    Node* root = nullptr;

    int n;
    cin >> n;
    if (n == 0) {
        cout << "YES";
        return 0;
    }

    int r;
    cin >> r;
    vector<Node> nodes(n);
    vector<pair<int, int>> children(n);
    for (int i = 0; i < n; ++i) {
        int num, key, left, right, cl = 0;
        char clr;
        cin >> num >> key >> left >> right >> clr;
        if (clr == 'B')  {
            cl = 1;
        }

        children[num - 1] = {left, right};

        nodes[num - 1] = Node(key, cl);
    }

    for (int i = 0; i < n; ++i) {
        
    } 
}
