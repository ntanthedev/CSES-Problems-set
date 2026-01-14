# 1751 - Planets Cycles

We start by noticing that the planets and teleporters form a graph where every
connected component is formed of a cycle and trees (possibly consisting of
only one planet) starting from each planet in the cycle. The answer for planet
$x$ is then the length of the cycle plus the number of teleports it takes
to reach the cycle.

We will process every component separately. We start processing a component by
finding the cycle (in this solution, using Floyd's tortoise and hare
algorithm). We will then run a depth-first search (DFS) from a cycle planet
in a graph where we have reversed all teleports. We additionally give the
DFS function the parameter $\mathrm{parent\\_answer}$, the answer for the parent
planet. For the first DFS function call this is just the number of
planets in the cycle. If the current planet is part of the cycle, the answer
for the current planet is just $\mathrm{parent\\_answer}$. If the current
planet is not part of the cycle, the answer is $\mathrm{parent\\_answer} + 1$.

The time complexity of the solution is $O(n)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;
const int N = 200001;

int teleporter[N];
vector<int> rev_graph[N];
bool cycle[N];
bool visited[N];
int answer[N];

// returns a pair (cycle node, length of the cycle)
std::pair<int, int> find_cycle(int x) {
    int a = x;
    int b = teleporter[x];
    while (a != b) {
        a = teleporter[a];
        b = teleporter[teleporter[b]];
    }
    int size = 0;
    do {
        ++size;
        cycle[a] = true;
        a = teleporter[a];
    } while (a != b);
    return {a, size};
}

void dfs(int x, int parent_answer) {
    if (visited[x]) return;
    visited[x] = true;
    answer[x] = parent_answer;
    if (!cycle[x]) ++answer[x];
    for (int y : rev_graph[x]) {
        dfs(y, answer[x]);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> teleporter[i];
        rev_graph[teleporter[i]].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            auto [x, size] = find_cycle(i);
            dfs(x, size);
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}
```