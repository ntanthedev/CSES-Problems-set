#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int power(int a, ll b) {
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
    ll n;
    cin >> n;

    ll sum = 0;
    if (n % 2 == 0) {
        sum += power(2, n * n);
        sum += power(2, n * n / 4);
        sum += power(2, n * n / 2);
        sum += power(2, n * n / 4);
    } else {
        sum += power(2, n * n);
        sum += power(2, (n / 2) * (n / 2 + 1) + 1);
        sum += power(2, n * (n / 2) + (n / 2 + 1));
        sum += power(2, (n / 2) * (n / 2 + 1) + 1);
    }
    ll answer = sum * inv(4) % M;
    cout << answer << "\n";
}
