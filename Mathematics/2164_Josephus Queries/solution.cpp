#include <iostream>
using namespace std;

int child(int n, int k, int p) {
    int r = (n + p) / 2;
    if (k <= r) return k * 2 - p;
    int u = n % 2 == 0 ? p : 1 - p;
    return child(n - r, k - r, u) * 2 - 1 + p;
}

int main() {
    int q;
    cin >> q;

    for (int qi = 1; qi <= q; qi++) {
        int n, k;
        cin >> n >> k;
        cout << child(n, k, 0) << "\n";
    }
}
