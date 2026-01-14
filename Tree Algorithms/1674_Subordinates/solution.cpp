#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int subordinates[N];

void dfs(int node) {
    for (int child : g[node]) {
        dfs(child);
        subordinates[node] += subordinates[child] + 1;
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i) {
        cout << subordinates[i] << ' ';
    }
    cout << '\n';
}
