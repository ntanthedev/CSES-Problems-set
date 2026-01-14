#include <iostream>
#include <vector>

using namespace std;

const int N = 200001;
const int INF = 1e9;
int teleport[N];
vector<int> rev_graph[N];
int answer[N];
// pairs of b, id
vector<pair<int, int>> queries[N];
int depth[N];
bool visited[N];

vector<int> extract_cycle(int x) {
    int a = x;
    int b = teleport[x];
    while (a != b) {
        a = teleport[a];
        b = teleport[teleport[b]];
    }
    vector<int> cycle;
    do {
        a = teleport[a];
        cycle.push_back(a);
    } while (a != b);
    return cycle;
}

void dfs(int x, int d) {
    visited[x] = true;
    int previous_depth = depth[x];
    depth[x] = d;
    for (auto [b, id] : queries[x]) {
        if (depth[b] > -INF) {
            answer[id] = d - depth[b];
        } else {
            answer[id] = -1;
        }
    }
    for (int y : rev_graph[x]) {
        if (!visited[y]) {
            dfs(y, d + 1);
        }
    }
    depth[x] = previous_depth;
}

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        teleport[i] = t;
        rev_graph[t].push_back(i);
        depth[i] = -INF;
    }
    for (int i = 1; i <= q; ++i) {
        int a, b;
        cin >> a >> b;
        queries[a].emplace_back(b, i);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            auto cycle = extract_cycle(i);
            for (int j = 1; j < cycle.size(); ++j) {
                depth[cycle[j]] = -j;
            }
            dfs(cycle[0], 0);
            for (int j = 1; j < cycle.size(); ++j) {
                depth[cycle[j]] = -INF;
            }
        }
    }

    for (int i = 1; i <= q; ++i) {
        cout << answer[i] << '\n';
    }
}
