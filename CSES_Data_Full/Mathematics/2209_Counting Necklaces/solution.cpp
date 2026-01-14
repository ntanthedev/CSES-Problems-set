#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int power(int a, int b) {
    if (b == 0) return 1;
    ll p = power(a, b / 2);
    p = p * p % M;
    if (b % 2 == 1) p = p * a % M;
    return p;
}

int inv(int x) {
    return power(x, M - 2);
}

int main() {
    int n, m;
    cin >> n >> m;

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += power(m, gcd(i, n));
        sum %= M;
    }
    ll answer = sum * inv(n) % M;
    cout << answer << "\n";
}
