#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<pair<int, int>> nodes;

    for (int i = 1; i <= n; ++i) {
        int deg;
        cin >> deg;
        if (deg > 0) {
            nodes.emplace(deg, i);
        }
    }

    vector<pair<int, int>> ans;

    while (!nodes.empty()) {
        auto [d, s] = nodes.top();
        nodes.pop();
        if (nodes.size() < d) {
            cout << "IMPOSSIBLE" << '\n';
            return 0;
        }
        vector<pair<int, int>> others;
        for (int t = 1; t <= d; ++t) {
            others.push_back(nodes.top());
            nodes.pop();
        }
        for (auto [a, b] : others) {
            ans.emplace_back(s, b);
            if (a > 1) {
                nodes.emplace(a - 1, b);
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b] : ans) {
        cout << a << ' ' << b << '\n';
    }
}
