#include <iostream>
using namespace std;
using ll = long long;

int power(int a, int b, int m) {
    if (b == 0) return 1 % m;
    ll p = power(a, b / 2, m);
    p = p * p % m;
    if (b % 2 == 1) p = p * a % m;
    return p;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << power(a, power(b, c, 1e9 + 6), 1e9 + 7) << "\n";
    }
}
