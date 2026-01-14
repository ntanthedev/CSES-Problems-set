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
