#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    queue<int> q;
    for (int i = 1; i <= n; ++i) q.push(i);

    vector<int> c(n, 0);
    int it = 0;
    for (; it < n - 4; ++it) {
        int x = q.front(); q.pop();
        if (a[it] != x && b[it] != x) {
            c[it] = x;
            continue;
        }
        int y = q.front(); q.pop();
        if (a[it] != y && b[it] != y) {
            c[it] = y;
            q.push(x);
            continue;
        }
        int z = q.front(); q.pop();
        c[it] = z;
        q.push(x);
        q.push(y);
    }

    vector<int> rem;
    while (!q.empty()) {
        rem.push_back(q.front());
        q.pop();
    }
    sort(rem.begin(), rem.end());

    bool found = false;
    do {
        bool ok = true;
        for (int i = 0; i < (int)rem.size(); ++i) {
            if (a[it + i] == rem[i] || b[it + i] == rem[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            found = true;
            for (int i = 0; i < (int)rem.size(); ++i) c[it + i] = rem[i];
            break;
        }
    } while (next_permutation(rem.begin(), rem.end()));

    if (!found) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << c[i];
    }
    cout << '\n';
    return 0;
}
