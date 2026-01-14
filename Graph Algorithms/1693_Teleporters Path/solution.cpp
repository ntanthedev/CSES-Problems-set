#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<int> cycle;

void fail() {
    cout << "IMPOSSIBLE\n";
    exit(0);
}

void find_cycle(int node) {
    while (!graph[node].empty()) {
        int next_node = graph[node].back();
        graph[node].pop_back();
        find_cycle(next_node);
    }
    cycle.push_back(node);
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    vector<int> in_degree(n + 1);
    vector<int> out_degree(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        out_degree[a]++;
        in_degree[b]++;
    }

    in_degree[1]++;
    out_degree[n]++;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] != out_degree[i]) fail();
    }

    find_cycle(1);
    if (cycle.size() != m + 1) fail();

    reverse(cycle.begin(), cycle.end());
    for (auto node : cycle) {
        cout << node << " ";
    }
    cout << "\n";
}
