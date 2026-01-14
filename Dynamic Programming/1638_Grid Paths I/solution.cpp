#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> paths(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '*') {
                paths[i][j] = 0;
            } else {
                paths[i][j] = i == 0 && j == 0;
                if (i) paths[i][j] += paths[i - 1][j];
                if (j) paths[i][j] += paths[i][j - 1];
                paths[i][j] %= M;
            }
        }
    }

    cout << paths[n - 1][n - 1] << "\n";
}
