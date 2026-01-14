#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();

    vector<vector<int>> distance(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) {
        distance[i][0] = i;
    }
    for (int j = 0; j <= m; ++j) {
        distance[0][j] = j;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            distance[i][j] = min({
                distance[i][j - 1] + 1,
                distance[i - 1][j] + 1,
                distance[i - 1][j - 1] + (a[i - 1] != b[j - 1]),
            });
        }
    }

    cout << distance[n][m] << "\n";
}
