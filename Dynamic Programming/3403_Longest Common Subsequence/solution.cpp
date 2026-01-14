#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    vector<vector<int>> lcs(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    cout << lcs[n][m] << "\n";

    vector<int> result;
    while (lcs[n][m] > 0) {
        if (a[n] == b[m]) {
            result.push_back(a[n]);
            n--;
            m--;
        } else if (lcs[n - 1][m] == lcs[n][m]) {
            n--;
        } else {
            m--;
        }
    }

    reverse(result.begin(), result.end());
    for (auto x : result) {
        cout << x << " ";
    }
    cout << "\n";
}
