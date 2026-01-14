#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    ll k;
    cin >> n >> k;

    int l = 1, r = n;
    for (int i = 1; i <= n; ++i) {
        int left = n - i;  // The amount of numbers left.
        // As r is larger than all remaining numbers,
        // adding it will form inversions with each one of them.
        if (left <= k) {
            k -= left;
            cout << r-- << ' ';
        } else {
            cout << l++ << ' ';
        }
    }
    cout << '\n';
}
