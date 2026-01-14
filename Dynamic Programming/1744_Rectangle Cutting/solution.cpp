#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int a, b;
    cin >> a >> b;

    vector<vector<int>> moves(a + 1, vector<int>(b + 1));
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            if (i == j) {
                moves[i][j] = 0;
            } else {
                moves[i][j] = INF;
                for (int x = 1; x < i; ++x) {
                    moves[i][j] =
                        min(moves[i][j], moves[x][j] + moves[i - x][j] + 1);
                }
                for (int y = 1; y < j; ++y) {
                    moves[i][j] =
                        min(moves[i][j], moves[i][y] + moves[i][j - y] + 1);
                }
            }
        }
    }

    cout << moves[a][b] << "\n";
}
