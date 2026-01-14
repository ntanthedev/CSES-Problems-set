#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n + 1);
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        pos[x[i]] = i;
    }

    int rounds = 1;
    for (int i = 2; i <= n; i++) {
        if (pos[i] < pos[i - 1]) rounds++;
    }

    auto change = [&](int k, int c) {
        if (k <= n && pos[k - 1] > pos[k]) rounds += c;
    };

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        change(x[a], -1);
        if (x[a] + 1 != x[b]) change(x[a] + 1, -1);
        change(x[b], -1);
        if (x[b] + 1 != x[a]) change(x[b] + 1, -1);
        swap(x[a], x[b]);
        pos[x[a]] = a;
        pos[x[b]] = b;
        change(x[a], 1);
        if (x[a] + 1 != x[b]) change(x[a] + 1, 1);
        change(x[b], 1);
        if (x[b] + 1 != x[a]) change(x[b] + 1, 1);
        cout << rounds << "\n";
    }
}
