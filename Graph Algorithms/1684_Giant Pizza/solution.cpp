#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct TwoSat {
    int n;
    vector<vector<int>> graph;
    vector<vector<int>> graph_rev;

    TwoSat(int n) : n(n), graph(2 * n), graph_rev(2 * n) {}

    void add_clause(int var1, int sign1, int var2, int sign2) {
        int node1 = 2 * var1 + sign1;
        int node2 = 2 * var2 + sign2;
        graph[node1 ^ 1].push_back(node2);
        graph[node2 ^ 1].push_back(node1);
        graph_rev[node2].push_back(node1 ^ 1);
        graph_rev[node1].push_back(node2 ^ 1);
    }

    vector<int> order, seen;

    void find_order(int node) {
        if (seen[node]) return;
        seen[node] = 1;
        for (auto next_node : graph[node]) {
            find_order(next_node);
        }
        order.push_back(node);
    }

    vector<int> component, new_order;

    void find_component(int node, int id) {
        if (component[node]) return;
        component[node] = id;
        for (auto next_node : graph_rev[node]) {
            find_component(next_node, id);
        }
        new_order.push_back(node);
    }

    vector<int> assignment;

    bool find_assignment() {
        seen.resize(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            find_order(i);
        }

        reverse(order.begin(), order.end());
        int count = 0;
        component.resize(2 * n);
        for (auto node : order) {
            if (component[node]) continue;
            count++;
            find_component(node, count);
        }

        for (int i = 0; i < n; i++) {
            int node = 2 * i;
            if (component[node] == component[node ^ 1]) {
                return false;
            }
        }

        assignment.resize(n);
        reverse(new_order.begin(), new_order.end());
        vector<bool> chosen(n);
        for (auto node : new_order) {
            int what = node / 2;
            if (chosen[what]) continue;
            chosen[what] = true;
            assignment[what] = node & 1;
        }

        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    TwoSat two_sat(m);

    for (int i = 1; i <= n; i++) {
        char sign1, sign2;
        int what1, what2;
        cin >> sign1 >> what1;
        cin >> sign2 >> what2;

        two_sat.add_clause(what1 - 1, sign1 == '+', what2 - 1, sign2 == '+');
    }

    bool result = two_sat.find_assignment();

    if (!result) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < m; i++) {
        cout << (two_sat.assignment[i] ? "+ " : "- ");
    }
    cout << "\n";
}
