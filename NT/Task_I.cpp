#include <bits/stdc++.h>

using namespace std;


int pw(int x, int p) {
    int n = x;
    int ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = ((long long)ans * x) % p;
        }

        x = ((long long)x * x) % p;
        n >>= 1;
    }

    return ans;
}


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a;
    cin >> a;
    int a_c = a;
    int ans = 1;
    for (int i = 2; i * i <= a; ++i) {
        if (a_c % i == 0) {
            ans *= i;
        }
        while (a_c % i == 0) {
            a_c /= i;
        }
    }


    if (a_c != 1) {
        ans *= a_c;
    }
    if (ans == a) {
        cout << ans;
        return 0;
    }
    for (int i = ans; i <= a; ++i) {
        if (pw(i, a) == 0) {
            cout << i;
            return 0;
        }
    }


    cout << a;
}