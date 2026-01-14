#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> count(n, vector<int>(n));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        count[a][b]++;
    }

    vector<vector<ll>> ways(1 << n, vector<ll>(n));
    ways[1][0] = 1;

    for (int mask = 2; mask < (1 << n); mask++) {
        vector<int> nodes;
        for (int node = 0; node < n; node++) {
            if (mask & (1 << node)) {
                nodes.push_back(node);
            }
        }

        for (auto last : nodes) {
            for (auto prev : nodes) {
                ways[mask][last] +=
                    count[prev][last] * ways[mask ^ (1 << last)][prev];
            }
            ways[mask][last] %= M;
        }
    }

    cout << ways[(1 << n) - 1][n - 1] << "\n";
}
