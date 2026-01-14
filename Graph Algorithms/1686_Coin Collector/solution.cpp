#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<vector<int>> graph;
vector<vector<int>> graph_rev;

vector<int> coins;

vector<int> order;
vector<int> seen;

void find_order(int node) {
    if (seen[node]) return;
    seen[node] = 1;
    for (auto next_node : graph[node]) {
        find_order(next_node);
    }
    order.push_back(node);
}

vector<int> component;
vector<vector<int>> nodes;
vector<ll> total_coins;

void find_component(int node, int id) {
    if (component[node]) return;
    component[node] = id;
    nodes[id].push_back(node);
    total_coins[id] += coins[node];
    for (auto next_node : graph_rev[node]) {
        find_component(next_node, id);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    coins.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> coins[i];
    }

    graph.resize(n + 1);
    graph_rev.resize(n + 1);

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph_rev[b].push_back(a);
    }

    seen.resize(n + 1);
    for (int node = 1; node <= n; node++) {
        find_order(node);
    }

    reverse(order.begin(), order.end());
    int count = 0;
    component.resize(n + 1);
    nodes.resize(n + 1);
    total_coins.resize(n + 1);
    for (auto node : order) {
        if (component[node]) continue;
        count++;
        find_component(node, count);
    }

    vector<ll> max_sum(count + 1);
    ll result = 0;
    for (int id = count; id >= 1; id--) {
        ll best_sum = 0;
        for (auto node : nodes[id]) {
            for (auto next_node : graph[node]) {
                if (component[next_node] != id) {
                    best_sum = max(best_sum, max_sum[component[next_node]]);
                }
            }
        }
        max_sum[id] = total_coins[id] + best_sum;
        result = max(result, max_sum[id]);
    }
    cout << result << "\n";
}
