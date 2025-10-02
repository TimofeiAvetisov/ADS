#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a, b;
    cin >> a >> b;
    if (a > b) {
        swap(a, b);
    }
    while (a != 0) {
        b %= a;
        if (a > b) {
            swap(a, b);
        }
    }

    cout << b;
}