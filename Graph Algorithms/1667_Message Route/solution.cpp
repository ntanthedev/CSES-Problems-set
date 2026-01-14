#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 100001;

vector<int> graph[N];
bool visited[N];
int parent[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    queue<int> queue;
    queue.push(1);
    visited[1] = true;

    while (!queue.empty()) {
        int x = queue.front();
        queue.pop();
        for (int y : graph[x]) {
            if (visited[y]) continue;
            visited[y] = true;
            parent[y] = x;
            queue.push(y);
        }
    }

    if (!visited[n]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> ans;
    int x = n;
    while (x != 0) {
        ans.push_back(x);
        x = parent[x];
    }
    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}
