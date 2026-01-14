#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
const int K = 100;
double p[K + 1][N * N][N][N];

int main() {
    int k;
    cin >> k;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            p[0][i * N + j][i][j] = 1;
        }
    }

    for (int m = 0; m < k; m++) {
        for (int r = 0; r < N * N; r++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    vector<pair<int, int>> moves;
                    if (i > 0) moves.emplace_back(i - 1, j);
                    if (j > 0) moves.emplace_back(i, j - 1);
                    if (i + 1 < N) moves.emplace_back(i + 1, j);
                    if (j + 1 < N) moves.emplace_back(i, j + 1);
                    double add = p[m][r][i][j] / moves.size();
                    for (auto d : moves) {
                        p[m + 1][r][d.first][d.second] += add;
                    }
                }
            }
        }
    }

    double answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double e = 1;
            for (int r = 0; r < N * N; r++) {
                e *= (1 - p[k][r][i][j]);
            }
            answer += e;
        }
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
