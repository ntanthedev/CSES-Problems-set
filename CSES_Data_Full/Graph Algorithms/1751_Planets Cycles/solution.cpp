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
