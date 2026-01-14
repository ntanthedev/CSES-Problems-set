#include <iostream>
#include <map>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000000;

int power(int a, int b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

int inv(int x) {
    return power(x, M - 2);
}

ll fac[N + 1];

int ncr(int a, int b) {
    return fac[a] * inv(fac[b] * fac[a - b] % M) % M;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }

    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (auto c : s) count[c]++;

    ll answer = 1;
    for (auto [c, k] : count) {
        answer = answer * ncr(n, k) % M;
        n -= k;
    }
    cout << answer << "\n";
}
