#include <iostream>
using namespace std;
const int MN = 1001;
string building[MN];
int n, m;

void dfs(int r, int c) {
    if (building[r][c] != '.') return;
    building[r][c] = '#';
    pair<int, int> deltas[]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (auto [dr, dc] : deltas) {
        int new_r = r + dr;
        int new_c = c + dc;
        if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
            dfs(new_r, new_c);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> building[i];
    }

    int n_rooms = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (building[i][j] == '.') {
                ++n_rooms;
                dfs(i, j);
            }
        }
    }
    cout << n_rooms << endl;
}
