#include <bits/stdc++.h>
#include <bitset>

using namespace std;

void print_binary(size_t bits_count) {

    for (int i = 0; i < (1<<bits_count); ++i) {
        cout << bitset<32>(i).to_string().substr(32 - bits_count) << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    print_binary(n);
}