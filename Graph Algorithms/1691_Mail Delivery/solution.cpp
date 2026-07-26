#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> eu(m), ev(m);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        eu[i] = a;
        ev[i] = b;
        adj[a].push_back(i);
        adj[b].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        if ((int)adj[i].size() % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> ptr(n + 1, 0);
    vector<char> used(m, 0);
    vector<int> st;
    st.push_back(1);
    vector<int> circuit;

    while (!st.empty()) {
        int v = st.back();
        while (ptr[v] < (int)adj[v].size() && used[adj[v][ptr[v]]])
            ptr[v]++;
        if (ptr[v] == (int)adj[v].size()) {
            circuit.push_back(v);
            st.pop_back();
        } else {
            int e = adj[v][ptr[v]++];
            if (used[e])
                continue;
            used[e] = 1;
            int u = eu[e] ^ ev[e] ^ v;
            st.push_back(u);
        }
    }

    if ((int)circuit.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    reverse(circuit.begin(), circuit.end());
    for (int i = 0; i <= m; i++) {
        if (i)
            cout << ' ';
        cout << circuit[i];
    }
    cout << '\n';
    return 0;
}
