# 1678 - Round Trip II

We solve the problem by running depth-first search (DFS) from
every previously unvisited city in the graph. If, while running some DFS,
we find a city that has a connection to a city currently
in the DFS stack then we have found a cycle.

Let's show that this algorithm indeed finds a cycle if a cycle exists.
Assume that there exists a cycle $x\_1, \dots, x\_k, x\_1$ and that the
algorithm doesn't find a cycle in the graph. The search will, however, visit
every node of the cycle. We'll assume that the first city of the cycle the
search visits is $x\_1$. Now, before popping $x\_1$ from the stack, the search
will eventually visit $x\_k$ and therefore find the cycle.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 100001;
vector<int> g[N];
bool visited[N];
bool active[N];
vector<int> answer;

bool dfs(int x) {
    if (active[x]) {
        answer.push_back(x);
        return true;
    }
    if (visited[x]) return false;
    visited[x] = true;
    active[x] = true;
    for (int y : g[x]) {
        if (dfs(y)) {
            answer.push_back(x);
            active[x] = false;
            return true;
        }
    }
    active[x] = false;
    return false;
}

int main() {
    int n, m;

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            if (dfs(i)) break;
        }
    }

    if (answer.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Erase elements after the last occurrence of `answer.front()`
    // `.base()` converts a reverse iterator to a forward iterator so that it
    // can be used with `.erase()`
    // If `r_it` is a reverse iterator corresponding to `it`, then
    // `r_it.base() == it + 1`
    auto last = find(answer.rbegin(), answer.rend(), answer.front());
    answer.erase(last.base(), answer.end());
    reverse(answer.begin(), answer.end());

    cout << answer.size() << '\n';
    for (int x : answer) {
        cout << x << ' ';
    }
    cout << '\n';
}
```