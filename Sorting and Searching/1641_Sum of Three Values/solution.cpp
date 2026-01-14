#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> v;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        v.emplace_back(a, i);
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        int y = x - v[i].first;
        int a = i + 1;
        int b = n - 1;
        while (a < b) {
            int s = v[a].first + v[b].first;
            if (s == y) {
                cout << v[i].second << " ";
                cout << v[a].second << " ";
                cout << v[b].second << "\n";
                return 0;
            } else if (s > y) {
                b--;
            } else {
                a++;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
