#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            vector<bool> seen(2 * n);
            for (int i = 0; i < y; i++) {
                seen[grid[i][x]] = true;
            }
            for (int i = 0; i < x; i++) {
                seen[grid[y][i]] = true;
            }
            while (seen[grid[y][x]]) {
                grid[y][x]++;
            }
            cout << grid[y][x] << " ";
        }
        cout << "\n";
    }
}
