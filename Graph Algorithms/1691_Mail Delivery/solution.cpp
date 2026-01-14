#include <iostream>
#include <set>
#include <vector>
using namespace std;

vector<set<int>> graph;
vector<int> cycle;

void fail() {
    cout << "IMPOSSIBLE\n";
    exit(0);
}

void find_cycle(int node) {
    while (!graph[node].empty()) {
        int next_node = *graph[node].begin();
        graph[node].erase(next_node);
        graph[next_node].erase(node);
        find_cycle(next_node);
    }
    cycle.push_back(node);
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    for (int i = 1; i <= n; i++) {
        if (graph[i].size() % 2 != 0) fail();
    }

    find_cycle(1);
    if (cycle.size() != m + 1) fail();

    for (auto node : cycle) {
        cout << node << " ";
    }
    cout << "\n";
}
