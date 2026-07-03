#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;

    vector<int> pos(m + 1, -1);
    for (int i = 0; i < m; i++) pos[b[i]] = i;

    vector<int> tail;
    vector<int> idx_at_len;
    vector<int> parent(n, -1);

    for (int i = 0; i < n; i++) {
        int v = a[i];
        if (v > m || pos[v] == -1) continue;
        int p = pos[v];
        auto it = lower_bound(tail.begin(), tail.end(), p);
        int len = (int)(it - tail.begin());
        if (len > 0) parent[i] = idx_at_len[len - 1];
        if (it == tail.end()) {
            tail.push_back(p);
            idx_at_len.push_back(i);
        } else {
            *it = p;
            idx_at_len[len] = i;
        }
    }

    cout << tail.size() << "\n";
    if (tail.empty()) {
        cout << "\n";
        return 0;
    }

    vector<int> seq;
    for (int i = idx_at_len.back(); i != -1; i = parent[i]) {
        seq.push_back(a[i]);
    }
    reverse(seq.begin(), seq.end());
    for (int i = 0; i < (int)seq.size(); i++) {
        if (i) cout << ' ';
        cout << seq[i];
    }
    cout << "\n";
}
