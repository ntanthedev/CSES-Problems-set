#include <iostream>
using namespace std;

const int N = 8;

string grid[N];
int total;
bool col[N], diag1[2 * N], diag2[2 * N];

void search(int y) {
    if (y == N) {
        total++;
        return;
    }
    for (int x = 0; x < N; x++) {
        if (grid[y][x] == '*') {
            continue;
        }
        if (col[x] || diag1[x + y] || diag2[y - x + N]) {
            continue;
        }
        col[x] = diag1[x + y] = diag2[y - x + N] = true;
        search(y + 1);
        col[x] = diag1[x + y] = diag2[y - x + N] = false;
    }
}

int main() {
    for (auto &row : grid) {
        cin >> row;
    }
    search(0);
    cout << total << "\n";
}
