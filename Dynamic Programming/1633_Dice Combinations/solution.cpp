#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<ll> ways(n + 1);
    ways[0] = 1;
    for (int i = 1; i <= n; ++i) {
        ways[i] = 0;
        for (int v = 1; v <= 6; ++v) {
            if (i - v >= 0) ways[i] += ways[i - v];
        }
        ways[i] %= M;
    }

    cout << ways[n] << "\n";
}
