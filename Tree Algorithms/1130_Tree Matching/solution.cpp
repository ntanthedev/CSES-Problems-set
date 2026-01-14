#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];

array<int, 2> dfs(int node, int parent) {
    auto dp = array{0, 0};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_dp = dfs(child, node);
        dp[1] = max({dp[0] + child_dp[0] + 1, dp[1] + child_dp[1],
                     dp[1] + child_dp[0]});
        dp[0] += max(child_dp[0], child_dp[1]);
    }
    return dp;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto result = dfs(1, 1);

    cout << max(result[0], result[1]) << '\n';
}
